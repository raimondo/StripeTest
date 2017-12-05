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
#import "PWPaymentParams.h"
#import "PWDebitCardParams.h"
#import "PWTokenParams.h"




/**
 * Use this class to create payment parameters.
 * 
 * Usually, you specify the amount, the currency, and the subject of a payment. Then, you add payment information, like card data for a credit or direct debit transaction. The other parameters are usually optional.
 * Sometimes, we require additional parameters, e.g. the geolocation of a payment. Please check back with us which data is needed in your case.
 * @warning Must be subclassed. Do not instantiate directly.
 */
@interface PWPaymentParamsFactory: NSObject

#pragma mark -- Credit card params

/** @name Create credit card params */

/**
 * Creates a PWPaymentParams object representing a credit card transaction
 * @param amount The amount of the transaction. Must be larger than zero.
 * @param currency The currency of the transaction
 * @param subject The description or subject of the transaction
 * @param ccNumber The credit card number of the transaction
 * @param cardholderName The name of the cardholder
 * @param expiryYear The expiration year. It is expected in the format YYYY
 * @param expiryMonth The expiration month of the credit card. It is expected in the format MM
 * @param CVV The cvv code associated with the credit card
 * @param latitude The latitude of the transaction in degrees. Same format as CLLocationCoordinate2D.latitude. I.e. The latitude in degrees. Positive values indicate latitudes north of the equator. Negative values indicate latitudes south of the equator.
 * @param longitude The longitude in degrees. Measurements are relative to the zero meridian, with positive values extending east of the meridian and negative values extending west of the meridian.
 * @param accuracy The radius of uncertainty for the location, measured in meters. (Same format as  CLLocation.horizontalAccuracy)
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a credit card transaction. nil is returned if an error occured. 
 */
-(PWPaymentParams*)createCreditCardPaymentParamsWithAmount: (double) amount currency:(PWCurrency) currency subject:(NSString*) subject ccNumber:(NSString *) ccNumber name: (NSString *) cardholderName expiryYear:(NSString *) expiryYear expiryMonth:(NSString *) expiryMonth CVV:(NSString *) CVV latitude: (double)latitude longitude: (double) longitude horizontalAccuracy: (double) accuracy error:(NSError **) error;
/**
 * Creates a PWPaymentParams object for tokenization of credit card details
 * @param number The credit card number of the transaction
 * @param cardholderName The name of the cardholder
 * @param expiryYear The expiration year. It is expected in the format YYYY
 * @param expiryMonth The expiration month of the credit card. It is expected in the format MM
 * @param CVV The cvv code associated with the credit card
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a tokenization transaction. nil is returned if an error occured.
 */
-(PWPaymentParams*)createCreditCardTokenizationParamsWithNumber: (NSString*) number name: (NSString*) cardholderName expiryYear: (NSString*) expiryYear expiryMonth: (NSString*) expiryMonth CVV: (NSString*) CVV error: (NSError**) error;


/**
 * Creates a PWPaymentParams object representing a credit card transaction which contains only basic information
 * @param amount The amount of the transaction. Must be larger than zero.
 * @param currency The currency of the transaction
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a credit card transaction. nil is returned if an error occured. 
 */

-(PWPaymentParams*)createCreditCardPaymentParamsWithAmount: (double) amount currency:(PWCurrency) currency error:(NSError **) error;

/**
 * Creates a PWPaymentParams object representing a credit card transaction with no information set
 * @return Returns a PWPaymentParams object representing a credit card transaction.
 */

-(PWPaymentParams*)createEmptyCreditCardPaymentParams;

/**
 * Create a PWPaymentParamsObject representing a credit card transaction from a generic payment params object
 * @param genericParams A generic Payment Params object. Only the data not specific to the payment scheme is copied to the new parameters.
 * @param ccNumber The credit card number of the transaction
 * @param cardholderName The name of the cardholder
 * @param expiryYear The expiration year. It is expected in the format YYYY
 * @param expiryMonth The expiration month of the credit card. It is expected in the format MM
 * @param CVV The cvv code associated with the credit card
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a credit card transaction. Or nil if an error occured. Take a look at the error object for details
 */
-(PWPaymentParams*)createCreditCardPaymentParamsWithPaymentParams:(PWPaymentParams*) genericParams ccNumber:(NSString *) ccNumber name: (NSString *) cardholderName expiryYear:(NSString *) expiryYear expiryMonth:(NSString *) expiryMonth CVV:(NSString *) CVV error:(NSError **) error;

/** @name Create direct debit params **/

#pragma mark -- Direct debit params

/**
 * Creates a PWPaymentParams object representing a direct debit transaction which contains only basic information
 * @param amount The amount of the transaction. Must be larger than zero.
 * @param currency The currency of the transaction
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a direct debit transaction. Or nil if an error occured. Take a look at the error object for details
 */

-(PWPaymentParams*)createDirectDebitPaymentParamsWithAmount: (double) amount currency:(PWCurrency) currency error:(NSError **) error;

/**
 * Creates a PWPaymentParams object representing a direct debit transaction with no information set
 * @return Returns a PWPaymentParams object representing a credit card transaction.
 */

-(PWPaymentParams*)createEmptyDirectDebitPaymentParams;

/** @name Create national direct debit params */


#pragma mark -- national Direct debit params

/**
 * Creates a PWPaymentParams object representing a direct debit transaction
 * @param amount The amount of the transaction. Must be larger than zero.
 * @param currency The currency of the transaction
 * @param subject The description or subject of the transaction
 * @param bankAccount The bank account number to be debited in the local format
 * @param bankNumber The bank number in the local format
 * @param bankCountryCode The country where the bank account is located in, according to ISO 3166-1
 * @param holderName The name of the cardholder
 * @param latitude The latitude of the transaction in degrees. Same format as CLLocationCoordinate2D.latitude. I.e. The latitude in degrees. Positive values indicate latitudes north of the equator. Negative values indicate latitudes south of the equator.
 * @param longitude The longitude in degrees. Measurements are relative to the zero meridian, with positive values extending east of the meridian and negative values extending west of the meridian.
 * @param accuracy The radius of uncertainty for the location, measured in meters. (Same format as  CLLocation.horizontalAccuracy)
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a direct debit transaction. Or nil if an error occurred. Take a look at the error object for details.
 */
-(PWPaymentParams*)createDirectDebitPaymentParamsWithAmount:(double) amount currency:(PWCurrency) currency subject:(NSString*) subject bankAccount:(NSString *) bankAccount bankNumber:(NSString*) bankNumber bankCountryCode:(NSString*) bankCountryCode name: (NSString *) holderName latitude: (double)latitude longitude: (double) longitude horizontalAccuracy: (double) accuracy error:(NSError **) error;

/**
 * Creates a PWPaymentParams object for tokenization of direct debit details
 * @param bankAccount The bank account number to be debited in the local format
 * @param bankNumber The bank number in the local format
 * @param bankCountryCode The country where the bank account is located in, according to ISO 3166-1
 * @param holderName The name of the cardholder
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a tokenization transaction. Or nil if an error occurred. Take a look at the error object for details.
 */
-(PWPaymentParams*) createDirectDebitTokenizationParamsWithBankAccount: (NSString*) bankAccount bankNumber: (NSString*) bankNumber bankCountryCode: (NSString*) bankCountryCode name: (NSString*) holderName error: (NSError**) error;




/**
 * Create a PWPaymentParamsObject representing a direct debit transaction from a generic payment params object
 * @param genericParams A generic Payment Params object. Only the data not specific to the payment scheme is copied to the new parameters.
 * @param bankAccount The bank account number to be debited in the local format
 * @param bankNumber The bank number in the local format
 * @param bankCountryCode The country where the bank account is located in, according to ISO 3166-1
 * @param holderName The name of the cardholder
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a direct debit transaction. Or nil if an error occurred. Take a look at the error object for details
 */
-(PWPaymentParams*)createDirectDebitPaymentParamsWithPaymentParams:(PWPaymentParams*) genericParams bankAccount:(NSString *) bankAccount bankNumber:(NSString*) bankNumber bankCountryCode:(NSString*) bankCountryCode name: (NSString *) holderName error:(NSError **) error;

/** @name Create national direct debit params */


#pragma mark -- international Direct debit params

/**
 * Creates a PWPaymentParams object representing a direct debit transaction with IBAN parameters
 * @param amount The amount of the transaction. Must be larger than zero.
 * @param currency The currency of the transaction
 * @param subject The description or subject of the transaction
 * @param IBAN The international bank account number to be debited
 * @param BIC The bank identification code
 * @param name The name of the cardholder
 * @param latitude The latitude of the transaction in degrees. Same format as CLLocationCoordinate2D.latitude. I.e. The latitude in degrees. Positive values indicate latitudes north of the equator. Negative values indicate latitudes south of the equator.
 * @param longitude The longitude in degrees. Measurements are relative to the zero meridian, with positive values extending east of the meridian and negative values extending west of the meridian.
 * @param accuracy The radius of uncertainty for the location, measured in meters. (Same format as  CLLocation.horizontalAccuracy)
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a direct debit transaction. Or nil if an error occurred. Take a look at the error object for details.
 */
-(PWPaymentParams*)createDirectDebitPaymentParamsWithAmount:(double) amount currency:(PWCurrency) currency subject:(NSString*) subject IBAN:(NSString *) iban BIC:(NSString*) bic name: (NSString *) holderName latitude: (double)latitude longitude: (double) longitude horizontalAccuracy: (double) accuracy error:(NSError **) error;

/**
 * Creates a PWPaymentParams object for tokenization of direct debit details
 * @param IBAN The international bank account number to be debited
 * @param BIC The bank identification code
 * @param name The name of the cardholder
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a tokenization transaction. Or nil if an error occurred. Take a look at the error object for details.
 */
-(PWPaymentParams*) createDirectDebitTokenizationParamsWithIBAN: (NSString*) iban BIC: (NSString*) bic name: (NSString*) holderName error: (NSError**) error;

/**
 * Create a PWPaymentParams object representing a direct debit transaction from a generic payment params object
 * @param genericParams A generic Payment Params object. Only the data not specific to the payment scheme is copied to the new parameters.
 * @param IBAN The international bank account number to be debited
 * @param BIC The bank identification code
 * @param name The name of the cardholder
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a direct debit transaction. Or nil if an error occurred. Take a look at the error object for details
 */
-(PWPaymentParams*)createDirectDebitPaymentParamsWithPaymentParams:(PWPaymentParams*) genericParams IBAN:(NSString *) iban BIC:(NSString*) bic name: (NSString *) holderName error:(NSError **) error;

/**
 * Create a PWPaymentParams object representing a direct debit transaction with IBAN parameters and a mandate ID.
 * @param amount The amount of the transaction. Must be larger than zero.
 * @param currency The currency of the transaction
 * @param subject The description or subject of the transaction
 * @param IBAN The international bank account number to be debited. Must not be nil.
 * @param BIC The bank identification code. Can be nil for a national transaction.
 * @param accountHolderName the name of the account holder. It depends on your acquirer if this is necessary. Contact us for details.
 * @param mandateId The SEPA mandate ID. Can be an arbitrary identifier. You need to keep track of the given mandate IDs, so you should assign unique IDs. Must not be nil.
 * @param dueDate The date when the payment should be due in format "yyyy-mm-dd". If nil, then the value is calculated accordingly to the acquirer bank and SEPA scheme rules. Contact us for details.
 * @param dateOfSignature The date on which the signature was provided, "yyyy-mm-dd". If nil, then the date of the transaction is used.
 * @return Returns a PWPaymentParams object representing a direct debit transaction. Or nil if an error occurred.
 */
-(PWPaymentParams*)createDirectDebitPaymentParamsWithAmount:(double) amount currency:(PWCurrency) currency subject: (NSString*) subject IBAN: (NSString*) IBAN BIC: (NSString*) BIC accountHolderName: (NSString*) accountHolderName mandateID: (NSString*) mandateId dueDate: (NSString*) dueDate dateOfSignature: (NSString*) dateOfSignature error: (NSError **) error;

/**
 * Create IBAN parameters with a mandate ID for tokenization. See createDirectDebitPaymentParamsWithAmount.
 */
-(PWPaymentParams*)createDirectDebitTokenizationParamsWithIBAN:(NSString *)iban BIC:(NSString *)bic accountHolderName: (NSString*) accountHolderName mandateID: (NSString*) mandateId dueDate: (NSString*) dueDate dateOfSignature: (NSString*) dateOfSignature error: (NSError **) error;


/** @name Create Debit card params */
#pragma mark -- Debit Card params

/**
 * Creates a PWPaymentParams object representing a debit card transaction
 * @param amount The amount of the transaction. Must be larger than zero.
 * @param currency The currency of the transaction
 * @param subject The description or subject of the transaction
 * @param type The type of the card
 * @param number The debit card number of the transaction
 * @param cardholderName The name of the cardholder
 * @param expiryYear The expiration year. It is expected in the format YYYY
 * @param expiryMonth The expiration month of the credit card. It is expected in the format MM
 * @param CVV The cvv code associated with the debit card
 * @param latitude The latitude of the transaction in degrees. Same format as CLLocationCoordinate2D.latitude. I.e. The latitude in degrees. Positive values indicate latitudes north of the equator. Negative values indicate latitudes south of the equator.
 * @param longitude The longitude in degrees. Measurements are relative to the zero meridian, with positive values extending east of the meridian and negative values extending west of the meridian.
 * @param accuracy The radius of uncertainty for the location, measured in meters. (Same format as  CLLocation.horizontalAccuracy)
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a debit card transaction. nil is returned if an error occurred.
 */
-(PWPaymentParams*)createDebitCardPaymentParamsWithAmount: (double) amount currency:(PWCurrency) currency subject:(NSString*) subject type: (PWDebitCardType) type number:(NSString *) number name: (NSString *) cardholderName expiryYear:(NSString *) expiryYear expiryMonth:(NSString *) expiryMonth CVV:(NSString *) CVV latitude: (double)latitude longitude: (double) longitude horizontalAccuracy: (double) accuracy error:(NSError **) error;
/**
 * Creates a PWPaymentParams object for tokenization of debit card details
 * @param type The debit card's type
 * @param number The debit card number of the transaction
 * @param cardholderName The name of the cardholder
 * @param expiryYear The expiration year. It is expected in the format YYYY
 * @param expiryMonth The expiration month of the debit card. It is expected in the format MM
 * @param CVV The cvv code associated with the debit card
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a tokenization transaction. nil is returned if an error occurred.
 */
-(PWPaymentParams*)createDebitCardTokenizationParamsWithType: (PWDebitCardType) type number: (NSString*) number name: (NSString*) cardholderName  expiryYear: (NSString*) expiryYear expiryMonth: (NSString*) expiryMonth CVV: (NSString*) CVV error: (NSError**) error;


/**
 * Creates a PWPaymentParams object representing a debit card transaction which contains only basic information
 * @param amount The amount of the transaction. Must be larger than zero.
 * @param currency The currency of the transaction
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a debit card transaction. nil is returned if an error occured.
 */

-(PWPaymentParams*)createDebitCardPaymentParamsWithAmount: (double) amount currency:(PWCurrency) currency error:(NSError **) error;

/**
 * Creates a PWPaymentParams object representing a debit card transaction with no information set
 * @return Returns a PWPaymentParams object representing a debit card transaction.
 */

-(PWPaymentParams*)createEmptyDebitCardPaymentParams;

/**
 * Create a PWPaymentParamsObject representing a debit card transaction from a generic payment params object
 * @param genericParams A generic Payment Params object. Only the data not specific to the payment scheme is copied to the new parameters.
 * @param type The debit card's type
 * @param number The debit card number of the transaction
 * @param issueNumber The card's issue number
 * @param cardholderName The name of the cardholder
 * @param startYear The start year in the format YYYY
 * @param startMonth The start month in the format MM
 * @param expiryYear The expiration year. It is expected in the format YYYY
 * @param expiryMonth The expiration month of the debit card. It is expected in the format MM
 * @param CVV The cvv code associated with the debit card
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a debit card transaction. Or nil if an error occured. Take a look at the error object for details
 */
-(PWPaymentParams*)createDebitCardPaymentParamsWithPaymentParams:(PWPaymentParams*) genericParams type: (PWDebitCardType) type number:(NSString *) dcNumber  name: (NSString*) cardholderName expiryYear:(NSString *) expiryYear expiryMonth:(NSString *) expiryMonth CVV:(NSString *) CVV error:(NSError **) error;

/** @name Create token params */


#pragma mark -- Token

/**
 * Create a PWPaymentParams Object representing a transaction using the data associated with a token
 * @param amount The amount of the transaction. Must be larger than zero.
 * @param currency The currency of the transaction
 * @param subject The description or subject of the transaction
 * @param token The token that is associated with the payment data
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing a token transaction. Or nil if an error occured. Take a look at the error object for details
 */
-(PWPaymentParams*)createTokenPaymentParamsWithAmount:(double) amount currency:(PWCurrency) currency subject:(NSString*) subject token:(NSString*) token error:(NSError **) error;

/**
 * Create a PWPWPaymentParams object with the given token and the data of the given payment params
 * @param token The token that is associated with the payment data
 * @param paymentParams The parameters to copy from (subject, name, customID, ...)
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentparams object representing a token transaction with the parameters copied from the provided parameters.
 */
-(PWPaymentParams*) createTokenPaymentParamsWithToken:(NSString*) token paymentParams:(PWPaymentParams*) params error:(NSError **) error;


/** @name Create generic payment params (for payment pages) */

#pragma mark -- Generic
/**
 * Creates a PWPaymentParams object representing a generic transaction. This can later be turned into another form of transaction, e.g. credit card or direct debit. Quite useful for the payment pages.
 * @param amount The amount of the transaction. Must be larger than zero.
 * @param currency The currency of the transaction
 * @param subject The description or subject of the transaction
 * @param latitude The latitude of the transaction in degrees. Same format as CLLocationCoordinate2D.latitude. I.e. The latitude in degrees. Positive values indicate latitudes north of the equator. Negative values indicate latitudes south of the equator.
 * @param longitude The longitude in degrees. Measurements are relative to the zero meridian, with positive values extending east of the meridian and negative values extending west of the meridian.
 * @param accuracy The radius of uncertainty for the location, measured in meters. (Same format as  CLLocation.horizontalAccuracy)
 * @param error A pointer to an NSError object
 * @return Returns a PWPaymentParams object representing generic payment paramters. Or nil if an error occured. Take a look at the error object for details
 */
-(PWPaymentParams*)createGenericPaymentParamsWithAmount: (double) amount currency:(PWCurrency) currency subject:(NSString*) subject latitude: (double)latitude longitude: (double) longitude horizontalAccuracy: (double) accuracy error:(NSError **) error;
/**
 * Creates generic params from arbitrary payment params. All information specific to a credit card or debit transaction are ignored. Quite useful for the payment pages.
 * @param amount The amount of the transaction. Must be larger than zero.
 * @param currency The currency of the transaction
 * @param error A pointer to an NSError object which gets populated if nil is returned
 * @return Returns a PWPaymentParams object representing generic payment parameters.
 */
-(PWPaymentParams*)createGenericPaymentParamsWithAmount: (double) amount currency:(PWCurrency) currency error:(NSError **) error;

/**
 * Creates generic params from arbitrary payment params. All information specific to a credit card or debit transaction are ignored. 
 * @param paymentParams the paymentParams to generate new generic payment params from
 * @param error A pointer to an NSError object
 * @return PWPaymentParams object representing generic payment params. Returns nil if an error occured or if the passed in params are also nil
 */
-(PWPaymentParams*)createGenericPaymentParamsWithPaymentParams:(PWPaymentParams*) paymentParams error:(NSError **) error;

/** @name Validate params */

#pragma mark -- Helpers
/**
 * Checks if the PWPaymentParameter object is filled with sufficient data to perform a transaction
 * @param params The parameters to be checked
 * @param error NSError object which is filled in case the method returns NO
 * @return YES if the parameters are sufficiently filled. NO if not, consult the filled NSError object for details
 *
 */
-(BOOL)areParametersValid:(PWPaymentParams *) params error:(NSError **) error;

/**
 * Checks if the PWPaymentParameter object is filled with sufficient data to perform a capture transaction. This is specific to the payment service provider used. Thus these checks are very conservative. Only the amount is checked currently.
 * @param params The parameters to be checked
 * @param error NSError object which is filled in case the method returns NO
 * @return YES if the parameters are sufficiently filled. NO if not, consult the filled NSError object for details
 *
 */
-(BOOL)areParametersValidForCapture:(PWPaymentParams *) params error:(NSError **) error;
@end
