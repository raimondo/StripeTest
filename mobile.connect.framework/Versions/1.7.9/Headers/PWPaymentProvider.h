//
// PAYWORKS GMBH ("COMPANY") CONFIDENTIAL
// Copyright (c) 2012 payworks GmbH, All Rights Reserved.
//
// NOTICE:  All information contained herein is, and remains the property of COMPANY. The intellectual and technical concepts contained 
// herein are proprietary to COMPANY and may be covered by European or foreign Patents, patents in process, and are protected by trade secret or copyright law.
// Dissemination of this information or reproduction of this material is strictly forbidden unless prior written permission is obtained
// from COMPANY.  Access to the source code contained herein is hereby forbidden to anyone except current COMPANY employees, managers or contractors who have executed
// Confidentiality and Non-disclosure agreements explicitly covering such access.
//
// The copyright notice above does not evidence any actual or intended publication or disclosure  of  this source code, which includes 
// information that is confidential and/or proprietary, and is a trade secret, of  COMPANY.   
// ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC  PERFORMANCE,
// OR PUBLIC DISPLAY OF OR THROUGH USE  OF THIS  SOURCE CODE  WITHOUT  THE EXPRESS WRITTEN CONSENT OF COMPANY IS STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE
// LAWS AND INTERNATIONAL TREATIES.  THE RECEIPT OR POSSESSION OF  THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS 
// TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING THAT IT  MAY DESCRIBE, IN WHOLE OR IN PART.

#import <Foundation/Foundation.h>
#import "PWTransaction.h"
@class PWPaymentParams;
@class PWPaymentParamsFactory;
@class PWAccountFactory;

// Enum for choosing an appropriate server type
typedef enum {
    PWTestServer,
    PWLiveServer
} PWServerType;

/**
 * Defines the methods and properties of the payment provider. Use the factory method getProviderWithName:andCredentials: to instantiate a new provider.
 */
@interface PWPaymentProvider : NSObject 

/**
 * Set this property to YES to get some debugging Info. This can be helpful when requesting technical support.
 */
@property (nonatomic) BOOL debugEnabled;
/**
 * The PWPaymentParamsFactory used for generating the PWPaymentParams associated with this PWPaymentProvider
 */
@property (nonatomic, strong) PWPaymentParamsFactory* paymentParamsFactory;

/**
 * The Account factory used for serializing and deserializing accounts
 */
@property (nonatomic, strong) PWAccountFactory* accountFactory;

/**
 * The name of the payment provider
 */
@property (nonatomic, strong) NSString* providerName;
 
/**
 * Determines the type of Server to use. Transactions to the LIVE server come with fees attached.
 */
@property (nonatomic) PWServerType serverType;

/** @name Create a new Transaction */
/**
 * Method creates and registers a transaction that can be used for performing a debit transaction. Depending on the PWPaymentParams a PWTransaction with the payment and provider specific processing is created. This method also registers the transaction with the processing system. This means the transaction is assigned a unique mobile identifier, which can be used for checking the status later on if the connection is interrupted or an unexpected error occurs. This makes sure that the status of a transaction can always be determined. This method works asynchronously as it needs to contact the processing system to obtain a unique mobile identifier. This does not process the transaction, i.e. no money is transfered. It is solely used to register the transaction:
 *
 * This framework is built to enable secure and reliable transaction processing, even in challenging mobile environments. The mobile identifier obtained when creating and registering the transaction can always be used to get the status of the current transaction. Make sure to save the identifier before processing a transaction.
 *
 * @param params The parameters in form of a PWPaymentParams object describing the transaction
 * @param success A Block executed when the transaction was processed successfully
 * @param failure A Block executed when the transaction processing failed
*/
-(void)createAndRegisterDebitTransactionWithParams:(PWPaymentParams *) params onSuccess:(void(^)(PWTransaction* transaction)) success onFailure:(void(^)(PWTransaction* transaction, NSError* error)) failure;

/**
 * Method creates and registers a transaction that can be used for preauthorizing a transaction. Depending on the PWPaymentParams a PWTransaction with the payment and provider specific processing is created. This method also registers the transaction with the processing system. This means the transaction is assigned a unique mobile identifier, which can be used for checking the status later on if the connection is interrupted or an unexpected error occurs. This makes sure that the status of a transaction can always be determined. This method works asynchronously as it needs to contact the processing system to obtain a unique mobile identifier. This does not process the transaction, i.e. no money is transfered. It is solely used to register the transaction:
 * 
 * This framework is built to enable secure and reliable transaction processing, even in challenging mobile environments. The mobile identifier obtained when creating and registering the transaction can always be used to get the status of the current transaction. Make sure to save the identifier before processing a transaction.
 *
 * @param params The parameters in form of a PWPaymentParams object describing the transaction
 * @param success A Block executed when the transaction was processed successfully
 * @param failure A Block executed when the transaction processing failed
*/
-(void)createAndRegisterPreauthorizationTransactionWithParams:(PWPaymentParams *) params onSuccess:(void(^)(PWTransaction* transaction)) success onFailure:(void(^)(PWTransaction* transaction, NSError* error)) failure;

/**
 * Method creates a transaction that can be captured. Depending on the subclass of PWPaymentParams a PWTransaction with the payment and provider specific processing is created. If the mobile identifier is specified, this transaction can be captured. Note that the mobile identifier must match the mobile identifier obtained when preauthorizing the transaction that now should be captured. What level of detail (e.g. Credit card number,...) the payment parameters must contain depends on processor/bank specific risk settings. The transaction created is in the state PWPreauthorized.
 * This does not process the transaction, i.e. no money is transfered. It is solely used to register the transaction:
 *
 * This framework is built to enable secure and reliable transaction processing, even in challenging mobile environments. The mobile identifier obtained when creating and registering the transaction can always be used to get the status of the current transaction. Make sure to save the identifier before processing a transaction.
 *
 * @param params The parameters in form of a PWPaymentParams object describing the transaction
 * @param mobileIdentifier The mobile identifier obtained when the initial transaction that now should be captured was successfully performed
 * @param success A Block executed when the transaction was processed successfully
 * @param failure A Block executed when the transaction processing failed
 */
-(void)createAndRegisterCaptureTransactionWithParams:(PWPaymentParams *) params mobileIdentifier:(NSString *) mobileIdentifier onSuccess:(void(^)(PWTransaction* transaction)) success onFailure:(void(^)(PWTransaction* transaction, NSError* error)) failure;

/**
 * Create and register a transaction that obtains a token for the given card data. This token can then be used to refer to specific card data without having to store it. The mobile identifier obtained when creating and registering the transaction can always be used to get the status of the current transaction. Make sure to save the identifier before processing a transaction.
 *
 * If successful, you will receive a transaction in the success block which you can then use with obtainToken:transaction. On failure, the failure block will be called, designating the error.
 *
 * @param params The parameters in form of a PWPaymentParams object describing the transaction. Can be parameters describing a credit or direct debit card.
 * @param success A Block executed when the transaction was registered successfully
 * @param failure A Block executed when the transaction registration failed
 */
-(void)createAndRegisterObtainTokenTransactionWithParams: (PWPaymentParams*) params onSuccess:(void (^) (PWTransaction* transaction)) success onFailure: (void (^) (PWTransaction*transaction, NSError* error)) failure;

/** @name Process transaction */
/**
 * On submitting a transaction, it is performed asynchronously using an NSURLConnection to communicate with the Server. Depending on the concrete type of the transaction, various calls to the server are necessary to ensure proper processing. Submitting means that the transaction is send to the server, where it will cause a debit of the given amount on the account specified in the PWTransaction's PWPaymentParams.
 *
 * A designated delegate is informed in case of success or failure. This framework is built to enable a secure and reliable transaction processing, even in challenging mobile environments. The mobile identifier obtained previously when creating the transaction, e.g. via createAndRegisterTransactionWithParams:andDelegate: can always be used to get the status of the current transaction. Make sure to save the identifier before processing a transaction.
 * 
 * @param transaction The transaction to be submitted
 * @param success A Block executed when the transaction was processed successfully
 * @param failure A Block executed when the transaction processing failed
 */
-(void)debitTransaction: (PWTransaction*) transaction onSuccess:(void(^)(PWTransaction* transaction)) success onFailure:(void(^)(PWTransaction* transaction, NSError* error)) failure;

/**
 * Preauthorizing and subsequently submitting a transaction is an alternative to directly submitting it. This two step process is sometimes refered to as Preauthorization (PA) and Capture (CP). Performing PA & CP gives the same result as submitting a transaction. What is performed in the preauthorization step is determined by the transaction type and the processor/bank. For a credit card payment, a preauthorization makes sure the requested funds are available on the account to be debited and reserves it for a given period of time (see e.g. http://www.shift4.com/process.cfm for the process involving a credit card payment). A preauthorization can also include risk checks and so forth.
 * Blocks are executed in the case of success or failure. This framework is built to enable a secure and reliable transaction processing, even in challenging mobile environments. The mobile identifier obtained previously when creating the transaction, e.g. via createAndRegisterPreauthorizationTransactionWithParams:mobileIdentifier:onSuccess:onFailure: can always be used to get the status of the current transaction. Make sure to save the identifier before processing a transaction.
 * 
 * @param transaction The transaction to be preauthorized
 * @param success A Block executed when the transaction was processed successfully
 * @param failure A Block executed when the transaction processing failed
 */ 
-(void)preauthorizeTransaction: (PWTransaction*) transaction onSuccess:(void(^)(PWTransaction* transaction)) success onFailure:(void(^)(PWTransaction* transaction, NSError* error)) failure;

/**
 * Preauthorizing and subsequently submitting a transaction is an alternative to directly submitting it. This two step process is sometimes refered to as Preauthorization (PA) and Capture (CP). Performing PA & CP gives the same result as submitting a transaction. What is performed in the preauthorization step is determined by the transaction type and the processor/bank. For a credit card payment, a preauthorization makes sure the requested funds are available on the account to be debited and reserves it for a given period of time (see e.g. http://www.shift4.com/process.cfm for the process involving a credit card payment). A preauthorization can also include risk checks and so forth.
 * Blocks are executed in the case of success or failure. This framework is built to enable a secure and reliable transaction processing, even in challenging mobile environments. The mobile identifier obtained previously when creating the transaction, via createAndRegisterCaptureTransactionWithParams:mobileIdentifier:onSuccess:onFailure: failure can always be used to get the status of the current transaction. Make sure to save the identifier before processing a transaction.
 *
 * @param transaction The transaction to be preauthorized
 * @param success A Block executed when the transaction was processed successfully
 * @param failure A Block executed when the transaction processing failed
 */
-(void)captureTransaction: (PWTransaction*) transaction onSuccess:(void(^)(PWTransaction* transaction)) success onFailure:(void(^)(PWTransaction* transaction, NSError* error)) failure;

/**
 * Obtain a token for the given credit or direct debit card data. Use the token to refer to this card in later transactions via PWTokenParams.
 *
 * @param transaction The transaction to be preauthorized
 * @param success A Block executed when the transaction was processed successfully. It is given the token that was assigned.
 * @param failure A Block executed when the transaction processing failed
 */
-(void)obtainToken: (PWTransaction*) transaction onSuccess:(void(^)(NSString* token, PWTransaction* transaction)) success onFailure:(void(^)(PWTransaction* transaction, NSError* error)) failure;



/**
 * Method used for getting the last known status of a transaction from the processing gateway. Use this if the internet connection was interrupted during processing of the transaction and the status was returned with PWUnknownTransactionStatus. The method returns the PWTransactionStatus of the transaction. Example Situation: You performed a preauthorization, i.e. registered and processed it, and you performed a capture afterwards (registration successful), but while receiving the response from the server when processing the transaction the internet connection broke down. Then you can use this method to check what state the transaction really is in. If the capture went through fine, this method will return PWVerified to the callback block, if not it will return PWPreauthorized to the callback block.
 * @param mobileIdentifier Identifier for the transaction to get the status for
 * @param success A Block executed when the query was processed successfully. This does not mean the transaction was successful, but rather that an answer from the server was obtained.
 * @param failure A Block executed when the query processing failed. This does not mean the transaction failed, but rather that an answer from the server could not be obtained.
 */
-(void)queryTransactionStatusForTransaction:(NSString*) mobileIdentifier onSuccessfulQuery:(void(^)(PWTransactionStatus lastSuccess)) success onQueryFailure:(void(^)(NSError* error)) failure;
/// Get credentials ///

/**
 * Method to get the credentials
 * @return Returns an array of NSString objects containing the credentials passed in to the provider
 */
-(NSArray*)credentials;

/**
 * @name Factory Methods
 */
/**
 * Deprecated, use [PWPaymentProvider getProviderWithApplicationId:profileToken] instead.
 */
+(PWPaymentProvider*) getProviderWithName:(NSString*) name andCredentials: (NSString*) credentials,... __attribute__((deprecated));

/**
 * Factory method to obtain a new provider. It takes the application Id followed by the profile token.
 *
 * @param applicationId This identifies your application. This is the same across each installation of your app.
 * @param profileToken This identifies the merchant and how the payment is routed. Depending on your application, you may want to retrieve the profile token from your backend.
 * @return A PWPaymentProvider which can be used to process transactions. nil is returned if the credentials are not set correctly.
 */
+(PWPaymentProvider*) getProviderWithApplicationId: (NSString*) applicationId profileToken: (NSString*) profileToken;

@end
