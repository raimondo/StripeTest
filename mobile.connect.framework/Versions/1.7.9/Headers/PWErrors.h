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
/**
Contains all error messages and codes that are possible (excluding error messages returned by the server).
 
To classify the errors broadly, the
 
 ____
 
    [error code];
 
 ____
 
 is used to encode what class or kind of an error is returned. The following values are used for the code attribute of the NSError object:
 
 - *PWPaymentParamsError*: Wrong information send in as a parameter. E.g. empty credit card number string
 - *PWProcessorError*: An error returned from the processor. This could be "Card invalid". Refer to the payment processors homepage for an exhaustive list of return codes
 - *PWSecurityError*: These errors indicatate that the security of the system has been compromised. E.g. if templates have been manipulated.
 - *PWTransactionStateError*: When trying to refund a transaction that has not been submitted, this error is thrown.
 
 Errors stemming from loss or lack of internet connectivity (i.e. NSURL callback errors) are handed down unmodified. Their [error code] can be seen, e.g. on https://developer.apple.com/library/mac/#documentation/Cocoa/Reference/Foundation/Miscellaneous/Foundation_Constants/Reference/reference.html

 
More detailed errors for the ones checked inside mobile.connect are encoded into the [NSError userInfo] NSDictionary. The relevant fields are the return code and the description of the error.
To retrieve the return code use e.g.
 
----
 
    (NSString *)[error.userInfo objectForKey:PWErrorCodeKey];
    (NSString *)[error.userInfo objectForKey:PWErrorDescriptionKey];
    (NSString *)[error.userInfo objectForKey:PWErrorDeveloperDescriptionKey];
 
----
 
The error codes currently sent by the system are:
 
*Payment Params error (11xx)*
 - 1101: Amount of transaction must be larger than zero
 - 1199: General error for invalid payment parameters (used as fallback, if no other code applies)
 - 1111: Direct Debit Bank Account should only contain numbers, dashes and capital letters. Credit Card numbers must pass the Luhn check.
 - 1112: Account holder must at least be composed of two names (first and last)
 - 1113: Country Parameter is expected in ISO 3166-1, i.e. two capital characters
 - 1114: Bank account has invalid bank code, i.e. in Germany bank codes are 8 digits for direct debi:
 - 1121: The card is expired
 - 1122: Month in invalid format. MM is expected
 - 1123: Year in invalid format. YYYY is expected
 - 1124: Invalid CVV, must be 3 or 4 digits
 - 1125: Invalid credit card brand. Currently only VISA, MasterCard, Diners, JCB, American Express are supported.
 - 1126: Card is not yet valid (for Debit cards that have a start date printed on them)
 - 1130: Reference mobile identifier is invalid. To perform this type of transaction a valid reference to a mobile identifier is needed.
 - 1131: ID of preauthorization transaction empty or in invalid format
 - 1132: Invalid payment method. Only Credit Card and Direct Debit are supported
 - 1133: Invalid token format.
 - 1134: Invalid token type.
 
*Transaction state error (12xx)*
 - 1201: Refund not possible before performing the transaction.
 - 1202: Transaction cannot be successfully refunded twice.
 - 1203: Transaction cannot be successfully refunded twice.
 - 1204: Transaction is in the wrong state to be submitted. Did you get the transaction from the correct PWPaymentProvider?
 - 1205: Transaction is in the wrong state to be captured. Has it been authorized before?
 - 1206: Transaction cannot be successfully preauthorized twice.
 - 1207: Transaction can only be reversed if there has been a preauthorization, a debit or a capture before.
 - 1208: Transaction needs to be registered before it is submitted. Have you created and registered it using a PWPaymentProvider?
 - 1209: Transaction to be attached to the signature needs to have a unique ID. Has it been submitted before?
 - 1221: The register block did not return successfully. Transactions not processed further after the registration. It has not been performed.
 - 1222: The payment page has been closed prematurely by the user. The transaction has not been performed.
 
*Security Errors (13xx)*
 - 1301: File loaded from resources does not have valid checksum. Make sure you installed the framework correctly and no one has been tampering with the application.
 - 1302: Can't validate ssl certificates for the connection. You might be tricked into connecting to the wrong host. Closing connection.

*Processing Error (4xxx)*
 - 4100: Server did not respond. Contact the system administrator of the server
 - 4200: Illegal server response. The response of the server could not be parsed while processing the transaction. This means it could not be determined if the transaction was successfully performed or not. The processing gateway knows the status of the transaction. Use the framework to check the status of the transaction!
 - 4201: Illegal server response. The response of the server could not be parsed when registering the transaction. Try registering the transaction again.
 - 4202: Illegal server response. The response of the server could not be parsed when querying the transaction status. Try querying again.
 - 4203: Illegal server response. The response of the server could not be parsed when persisting the customer verification for a transaction. Try persisting the verification transaction again.
 - 4300: Connection lost during processing. The connection was interrupted during processing and could not be recovered. This means it could not be determined if the transaction was successfully performed or not. The processing gateway knows the status of the transaction. Use the framework to check the status of the transaction!
 - 4301: Connection lost during registering a transaction. The connection was interrupted during the registration of a transaction. Try registeringthe transaction again.
 - 4302: Connection lost during querying a transaction. The connection was interrupted during querying the transaction status and could not be recovered. Try querying again.
 - 4303: Connection lost during persisting the customer verification for a transaction. The connection was interrupted during persisting the customer verification and could not be recovered. Try persisting the verification of the transaction again.
 
Additional error codes are passed down from the processing provider, e.g. as error codes 5xxx and 6xxx as well as xxx.xxx.xxx . Review a list of your processing provider for more details.
*/
#import <Foundation/Foundation.h>


typedef enum {
    PWPaymentParamsError = 815101, // 0815 error codes
    PWProcessingError = 815102,
    PWSecurityError = 815103,
    PWTransactionStateError = 815104
} PWErrorClass;

@interface PWErrors : NSObject

extern NSString * const PWErrorDomain;

/** Keys for identifying the data sent in the dictionary accompanying the NSError */
extern NSString * const PWErrorCodeKey;
extern NSString * const PWErrorDescriptionKey;
extern NSString * const PWErrorDeveloperDescriptionKey;


/** Error Codes and accompanied messages */

extern NSString * const PWPaymentParamsNotValidCode;
extern NSString * const PWPaymentParamsNotValidText;

extern NSString * const PWPaymentParamsAmountNotPositiveCode;
extern NSString * const PWPaymentParamsAmountNotPositiveText;

extern NSString * const PWPaymentParamsMonthInvalidFormatCode;
extern NSString * const PWPaymentParamsMonthInvalidFormatText;

extern NSString * const PWPaymentParamsYearInvalidFormatCode;
extern NSString * const PWPaymentParamsYearInvalidFormatText;

extern NSString * const PWPaymentParamsCardExpiredCode;
extern NSString * const PWPaymentParamsCardExpiredText;

extern NSString * const PWPaymentParamsCardNotYetValidCode;
extern NSString * const PWPaymentParamsCardNotYetValidText;


extern NSString* const PWPaymentParamsInvalidIBANCode;
extern NSString* const PWPaymentParamsInvalidIBANText;

extern NSString* const PWPaymentParamsInvalidBICCode;
extern NSString* const PWPaymentParamsInvalidBICText;

extern NSString * const PWPaymentParamsCreditCardNumberInvalidCode;
extern NSString * const PWPaymentParamsCreditCardNumberInvalidText;

extern NSString * const PWPaymentParamsInvalidCreditCardBrandCode;
extern NSString * const PWPaymentParamsInvalidCreditCardBrandText;

extern NSString * const PWPaymentParamsInvalidHolderCode;
extern NSString * const PWPaymentParamsInvalidHolderText;

extern NSString * const PWPaymentParamsInvalidCVVCode;
extern NSString * const PWPaymentParamsInvalidCVVText;

extern NSString * const PWPaymentParamsInvalidBankAccountCode;
extern NSString * const PWPaymentParamsInvalidBankAccountText;

extern NSString * const PWPaymentParamsInvalidBankNumberCode;
extern NSString * const PWPaymentParamsInvalidBankNumbertText;

extern NSString * const PWPaymentParamsInvalidBankNameCode;
extern NSString * const PWPaymentParamsInvalidBankNameText;

extern NSString * const PWPaymentParamsInvalidBankCountryCode;
extern NSString * const PWPaymentParamsInvalidBankCountryText;

extern NSString * const PWPaymentParamsInvalidReferenceIDCode;
extern NSString * const PWPaymentParamsInvalidReferenceIDText;

extern NSString * const PWPaymentParamsInvalidPreAuthIDCode;
extern NSString * const PWPaymentParamsInvalidPreAuthIDText;

extern NSString * const PWPaymentParamsInvalidMethodCode;
extern NSString * const PWPaymentParamsInvalidMethodText;

extern NSString * const PWPaymentParamsInvalidTransactionTypeCode;
extern NSString * const PWPaymentParamsInvalidTransactionTypeText;

extern NSString * const PWPaymentParamsInvalidTokenFormatCode;
extern NSString * const PWPaymentParamsInvalidTokenFormatText;

extern NSString * const PWPaymentParamsInvalidTokenTypeCode;
extern NSString * const PWPaymentParamsInvalidTokenTypeText;

extern NSString * const PWSecurityXMLmanipulationCode;
extern NSString * const PWSecurityXMLmanipulationText;

extern NSString * const PWSecurityCantValidateCertificateCode;
extern NSString * const PWSecurityCantValidateCertificateText;

extern NSString * const PWTransactionStateCantRefundBeforeSubmitErrorCode;
extern NSString * const PWTransactionStateCantRefundBeforeSubmitErrorText;

extern NSString * const PWTransactionStateCantSubmitAgainErrorCode;
extern NSString * const PWTransactionStateCantSubmitAgainErrorText;

extern NSString * const PWTransactionStateCantPreauthAgainErrorCode;
extern NSString * const PWTransactionStateCantPreauthAgainErrorText;

extern NSString * const PWTransactionStateCantRefundAgainErrorCode;
extern NSString * const PWTransactionStateCantRefundAgainErrorText;

extern NSString * const PWTransactionStateCantSubmitErrorCode;
extern NSString * const PWTransactionStateCantSubmitErrorText;

extern NSString * const PWTransactionStateCantCaptureBeforeAuthErrorCode;
extern NSString * const PWTransactionStateCantCaptureBeforeAuthErrorText;

extern NSString * const PWTransactionStateCantReverseErrorCode;
extern NSString * const PWTransactionStateCantReverseErrorText;

extern NSString * const PWTransactionStateNotRegisteredErrorCode;
extern NSString * const PWTransactionStateNotRegisteredErrorText;

extern NSString * const PWTransactionStateRegisteredCallbackFailedErrorCode;
extern NSString * const PWTransactionStateRegisteredCallbackFailedErrorText;

extern NSString * const PWTransactionStatePaymentPageClosedErrorCode;
extern NSString * const PWTransactionStatePaymentPageClosedErrorText;

extern NSString * const PWPersistSignatureNoUniqueIDErrorCode;
extern NSString * const PWPersistSignatureNoUniqueIDErrorText;

extern NSString * const PWServerIllegalArgumentsErrorCode;
extern NSString * const PWServerIllegalArgumentsErrorText;

extern NSString * const PWServerDidNotRespondErrorCode;
extern NSString * const PWServerDidNotRespondErrorText;

extern NSString * const PWServerNotAuthorizedErrorCode;
extern NSString * const PWServerNotAuthorizedErrorText;

extern NSString * const PWServerIllegalResponseErrorCode;
extern NSString * const PWServerIllegalResponseErrorText;

extern NSString * const PWServerProcessorErrorCode;
extern NSString * const PWServerProcessorErrorText;

extern NSString * const PWServerIllegalResponseRegisterErrorCode;
extern NSString * const PWServerIllegalResponseRegisterErrorText;

extern NSString * const PWServerIllegalResponseQueryErrorCode;
extern NSString * const PWServerIllegalResponseQueryErrorText;

extern NSString * const PWServerIllegalResponsePersistErrorCode;
extern NSString * const PWServerIllegalResponsePersistErrorText;

extern NSString * const PWServerConnectionLostErrorCode;
extern NSString * const PWServerConnectionLostErrorText;

extern NSString * const PWServerConnectionLostRegisterErrorCode;
extern NSString * const PWServerConnectionLostRegisterErrorText;

extern NSString * const PWServerConnectionLostQueryErrorCode;
extern NSString * const PWServerConnectionLostQueryErrorText;

extern NSString * const PWServerConnectionLostPersistErrorCode;
extern NSString * const PWServerConnectionLostPersistErrorText;

/**
 * Method to return an NSError for a specific error code and description
 * @param errorClass The error class, specifying the general type of the error
 * @param errorCode The error code, as listed above
 * @param description A NSString describing the error in more detail
 */
+(NSError*)getErrorForErrorClass:(PWErrorClass) errorClass withErrorCode:(NSString*) errorCode description:(NSString*) description;

/**
 * Method to return an NSError for a specific error code and description
 * @param errorClass The error class, specifying the general type of the error
 * @param errorCode The error code, as listed above
 * @param description A NSString describing the error in more detail
 * @param developerDescription A description giving the developer more information about the application
 */
+(NSError*)getErrorForErrorClass:(PWErrorClass) errorClass withErrorCode:(NSString*) errorCode description:(NSString*) description andDeveloperDescription:(NSString*) developerDescription;
@end
