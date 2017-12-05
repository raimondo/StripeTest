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

/**
 * Encapsulates all necessary transaction parameters for performing a direct debit transaction.
 */
@interface PWDirectDebitParams : PWPaymentParams

/** @name Mandatory Properties */
/** The holder of the bank account */
@property (nonatomic, strong) NSString *ddName;
/** @name Either use domestic bank account details */
/** The domestic bank account number of the holder*/
@property (nonatomic, strong) NSString *ddBankAccount;
/** The domestic code of the bank which holds the direc debit account of the holder*/
@property (nonatomic, strong) NSString *ddBankNumber;
/** The country where the bank account is located in, according to ISO 3166-1 */
@property (nonatomic, strong) NSString *ddBankCountryCode;
/** @name Or use IBAN and BIC */
/** The international bank account number. */
@property (nonatomic, strong) NSString *ddIBAN;
/** The bank identifier code. */
@property (nonatomic, strong) NSString *ddBIC;
/** The mandate ID */
@property (nonatomic, strong) NSString *ddMandateId;
/** The due date */
@property (nonatomic, strong) NSString *ddDueDate;
@property (nonatomic, strong) NSString *ddDateOfSignature;

/** @name Country specific Properties */
/** The name of the bank: Necessary only for Austria and the Netherlands */
@property (nonatomic, strong) NSString *ddBankName;

/**
 * Checks if a country / bank number combination is valid
 * Currently only for Germany (8 digits) and Italy (empty)
 * @return YES if the bank number is valid and NO if it is not valid. Also returns NO if either the bank number or country code are "nil"
 */
-(BOOL)isddBankNumberValidForCountry;

/**
 * Checks if the bank account number is masked or not
 * @return Returns YES if masked with "xxxx" except last 2 and NO if not. Returns YES for empty string */
-(BOOL) isBANumberMasked;

/**
 * Masks the bank account number by replacing the first all digits with "xxxx" except the last 2 digits.
 */
-(void) maskBANumber;

/**
 * Mask the IBAN by removing all except the last 2 digits.
 */
-(void) maskIBAN;

/**
 * Create the masked version of the Bank Account Number. It replaces the BA number with "xxxx" except the last 2 digits.
 * @return The Bank Account number masked. Returns nil if the bank account number is empty
 */
-(NSString *)maskedBANumber;

/**
 * @return If these params contain international parameters (IBAN, BIC)
 */
-(BOOL)hasInternationalParameters;

@end
