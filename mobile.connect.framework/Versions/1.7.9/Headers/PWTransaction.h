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
@class PWTransactionProcessor;
@class PWPaymentParams;

// enum containing the detailed status of a transaction
typedef enum {
    // When the transaction is first created it is in PWInitializedNotProcessed
    PWInitializedNotProcessed,
    // After performing a preauthorization
    PWPreauthorized,
    // If the transaction went through fine
    PWVerified,
    // If the transaction was successfully reversed
    PWReversed,
    // If the transaction has been refunded
    PWRefunded,
    PWUnknownTransactionStatus = -1
} PWTransactionStatus;

/**
 * Class which serves as a superclass of various concrete transactions.
 *
 * @warning Do not instantiate directly. Use the provided factory methods in the concrete subclass of a PWPaymentProvider.
 */
@interface PWTransaction : NSObject 

/** @name Properties */
/** The parameters representing a concrete payment method are kept as a PWPayementParams object */
@property (nonatomic, strong) PWPaymentParams *paymentParams;

/** The status of the transaction as defined by the corresponding enum. The normal status cycle of a transaction starts with PWInitializedNotProcessed as soon as it has been registered. Upon successful processing it is in PWPreauthorized or PWVerified, depending on whether a preauthorization or a debit transaction has been done. When the transaction is in the state PWInitializedNotProcessed this means it has not been processed and processing can be done. If an unrecoverable error occurs during processing and the transmission has been cut off in such a way that the SDK does not know the status of the transaction it is in PWUnknownTransactionStatus and the query interface of the PWPaymentProvider can be used to find out the status. */
@property (nonatomic) PWTransactionStatus status;

/** The unique mobile transaction ID used to identify every transaction */
@property (nonatomic, strong) NSString* mobileIdentifier;

/** @name Processer Specific Properties */

/** The unique transaction identifier as provided by the processing system. This identifier needs to be used when using specific properties of the processing system (not only mobile transactions) */
@property (nonatomic, strong) NSString *processorIdentifier;

/** A short identifier to represent the transaction in the processing system. Note, that this is not unique. */
@property (nonatomic, strong) NSString *processorShortIdentifier;

/** Contains the timestamp as returned by the processing server */
@property (nonatomic, strong) NSDate *processorTimestamp;

/** @name Process transaction */
/**
 * Transactions should be processed using PWPaymentProvider methods, such as **submitTransaction: withDelegate:**,**preauthorizeTransaction: withDelegate:** etc.
 */
@end
