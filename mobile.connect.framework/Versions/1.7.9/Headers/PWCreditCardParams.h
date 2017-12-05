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

// enum containing the different credit card types
typedef enum {
    PWMaster,
    PWVisa,
    PWJCB,
    PWDiners,
    PWAmex,
    PWUnknownCreditCard = - 1
} PWCreditCardType;

/**
 * Represents a set of credit card parameters needed for performing an e-commerce credit card transaction.
 * 
 * It offers convience methods for checking if the number is valid, i.e. if it passes the lauhn check and can be assigned to one of the major credit card companies.
 *
 * After getting an authorization for the transaction the parameters are masked in accordance to PCI PA DSS requirements.
 */

@interface PWCreditCardParams : PWPaymentParams 

/** @name Properties */
/** The name of the credit card owner. Is cut if longer than 100 characters */
@property (nonatomic, retain) NSString *ccName;
/** The card type is automatically detected from the credit card number. */
@property (nonatomic) PWCreditCardType ccType;
/** The credit card number. It may contain spaces " " and dashes "-" */
@property (nonatomic, retain) NSString *ccNumber;
/** The credit expiry month in the format MM */
@property (nonatomic, retain) NSString *ccExpiryMonth;
/** The credit expiry year in the format YYYY */
@property (nonatomic, retain) NSString *ccExpiryYear;
/** The CVV code found on the credit card. This is needed for e-commerce transactions */
@property (nonatomic, retain) NSString *ccCVV;

/** @name Parameter Checks */

/**
 * Checks if the number passes the Luhn Test http://en.wikipedia.org/wiki/Luhn_algorithm
 * @return YES if the number passes the Luhn test and NO if it doesn't
 * @param ccNumber Credit card number without any whitespaces or other characters
 */
+(BOOL) isCCNumberValid:(NSString*) ccNumber;

/**
 * Checks if the current credit card number passes the Luhn Test http://en.wikipedia.org/wiki/Luhn_algorithm
 * @return YES if the current credit card number passes the Luhn test and NO if it doesn't
 */
-(BOOL) isCurrentCCNumberValid;

/**
 * Checks if all parameters have been set correctly. Since parameters are checked in the respective setter methods, this method only checks if they are not empty.
 * @return Returns YES if all parameters have been set correctly and NO if one or more parameters is still empty.
 */
-(BOOL) areParametersValid;

/**
 * Checks if the Credit Card number is masked or not
 * @return Returns YES if masked with "xxxxxxxxxxxx" at the first 12 places and NO if not. Returns YES for empty string */
-(BOOL) isCcNumberMasked;

/**
 * Masks the credit card number by replacing the first 12 digits with "xxxxxxxxxxxx".
 */
-(void) maskCcNumber;
/**
 * Returns a masked form of the current Credit Card number. It replaces the first 12 digits with "xxxxxxxxxxxx"
 * @return The current credit card number masked. Returns nil if the credit card number is empty
 */
-(NSString*) maskedCcNumber;

/**
 * Checks if the month and year have been set and whether or not card is expired
 * @return YES if the month or the year have not been set. And NO if the card is not expired yet
 */
-(BOOL) isCardExpired;

/** Helper method to convert String to PWCreditCardType 
 * @param type String description of the credit card type
 */
+(PWCreditCardType) ccTypeEnum:(NSString *) type;
/** Helper method to convert String from xml to PWCreditCardType 
 * @param type String description of the credit card type
 */
+(PWCreditCardType) paymentEnum:(NSString *) type;
/** Helper method to convert PWCreditCardType to string needed for xml
 * @param type Credit card type to converted to string
 */
+(NSString *) paymentXMLString:(PWCreditCardType) type;

@end
