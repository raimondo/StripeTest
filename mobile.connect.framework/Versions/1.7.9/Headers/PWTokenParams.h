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

#import "PWPaymentParams.h"

typedef enum {
    PWCreditToken,
    PWDirectDebitToken,
    PWDebitToken,
    PWUnknownTokenType
} PWTokenType;

/**
 * Encapsulates parameters for the transaction with a token
 */
@interface PWTokenParams : PWPaymentParams

/** @name Mandatory Properties */
/** The token that is associated with payment data, obtained through a transaction */
@property (nonatomic, strong) NSString *token;

/** Indicates which type of card (e.g. credit) is associated with this token. */
@property (nonatomic) PWTokenType tokenType;

/**
 * Returns the raw token, i.e. the token without the type prefix.
 */
-(NSString*) rawToken;

/** Check if given string has the valid format of a token
 * @param token the token to check the format
 */
+(BOOL) isValidTokenFormat:(NSString*) token;

/** Check if a token's type is valid 
 * @param token the token to check the type
 */
+(BOOL) isValidTokenType:(NSString*) token;

/** Extract the type of the token.
 * If the type cannot be recognized, NULL is returned instead.
 * @param token the token to extract the type from.
 */
+(PWTokenType) tokenType:(NSString*) token;

/**
 * Get the prefix for the given token type.
 * @param type the type to get the prefix for.
 */
+(NSString*) tokenPrefixForType: (PWTokenType) type;

/**
 * Get the prefix for the given payment parameters.
 * @param params the type to get the prefix for.
 */
+(NSString*) tokenPrefixForParams: (PWPaymentParams*) params;

/**
 * Add the prefix given by the payment parameters to the raw token
 * Both parameters must not be nil.
 * @param rawToken the token to add the prefix
 * @param paymentParams the parameters to get the prefix from.
 */
+(NSString*) addPrefix: (NSString*) rawToken params: (PWPaymentParams*) paymentParams;
@end
