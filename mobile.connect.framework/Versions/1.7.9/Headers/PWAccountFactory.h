//
//  PWAccountFactory.h
//  payworks.connect
//
//  Created by Korbinian Breu on 8/8/13.
//
//

#import <Foundation/Foundation.h>
#import "PWPaymentParams.h"

@interface PWAccountFactory : NSObject


- (NSArray*) deserializeAccounts: (NSString*) encoded;

- (NSString*) serializeAccounts: (NSArray*) accounts;

@end
