//
//  ViewController.m
//  StripeTest
//
//  Created by Ray de Rose on 2017/11/07.
//  Copyright © 2017 Ray de Rose. All rights reserved.
//

#import "ViewController.h"
#import <Firebase/Firebase.h>
#import <mobile.connect/mobile.connect.h>
#import <OPPWAMobile/OPPWAMobile.h>



@interface ViewController ()
{
    BOOL chargeButtonAdded;
    UIActivityIndicatorView * spinner;
    NSString *uuid;
    UIButton *  chargeButton;
    STPCardParams *cardParams;
}

@property(nonatomic,strong) STPPaymentCardTextField * chargeTextField;

//@property (strong, nonatomic) PWPaymentProvider *provider;
@property (nonatomic) OPPPaymentProvider *provider;


@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    STPPaymentCardTextField * cardVC = [[STPPaymentCardTextField alloc]initWithFrame:CGRectMake(30,200, [UIScreen mainScreen].bounds.size.width-60, 50)];
    cardVC.textColor = [UIColor whiteColor];
    cardVC.delegate = self;
    [cardVC becomeFirstResponder];
    [self.view addSubview:cardVC];
    
    chargeButton = [UIButton buttonWithType:UIButtonTypeCustom];
    chargeButton.frame = CGRectMake(30,300, [UIScreen mainScreen].bounds.size.width-60, 40);
    chargeButton.backgroundColor = [UIColor clearColor];
    [chargeButton setTitle:@"Submit"  forState:UIControlStateNormal];
    [chargeButton setTitle:@"Submit"  forState:UIControlStateSelected];
    [chargeButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [chargeButton setTitleColor:[UIColor clearColor] forState:UIControlStateHighlighted];
    [chargeButton setTitleColor:[UIColor clearColor] forState:UIControlStateSelected];
    chargeButton.titleLabel.font = [UIFont systemFontOfSize:14];
    
    chargeButton.imageEdgeInsets = UIEdgeInsetsMake(8, 8, 8, 8);
    chargeButton.layer.cornerRadius = 5;
    chargeButton.layer.masksToBounds = YES;
    chargeButton.layer.borderColor =   [UIColor lightGrayColor].CGColor;
    chargeButton.layer.borderWidth = 1;
    [chargeButton addTarget:self action:@selector(submitPressed) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:chargeButton];
    
    spinner = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
    [spinner setCenter:CGPointMake(20, chargeButton.bounds.size.height/2)];
    [chargeButton addSubview:spinner];
    chargeButton.hidden = YES;
    
    self.provider = [OPPPaymentProvider paymentProviderWithMode:OPPProviderModeTest];


}







- (void)paymentCardTextFieldDidChange:(STPPaymentCardTextField *)textField
{
    if (textField.isValid)
    {
        if (!chargeButtonAdded)
        {
            chargeButtonAdded = YES;
            [self addchargeButton:textField];
        }
    }
}


-(void)addchargeButton:(STPPaymentCardTextField *)textField
{
    chargeButton.hidden = NO;
    _chargeTextField = textField;
}


-(OPPCardPaymentParams*)validateShopperDetails:(NSString*)checkoutID :(STPCardParams *)cardParams
{
    NSError *error = nil;
     FIRUser *user = [FIRAuth auth].currentUser;
    OPPCardPaymentParams *params = [OPPCardPaymentParams cardPaymentParamsWithCheckoutID:checkoutID
                                                                            paymentBrand:@"VISA"
                                                                                  holder:user.displayName
                                                                                  number:cardParams.number
                                                                             expiryMonth:[NSString stringWithFormat:@"%lu", (unsigned long)cardParams.expMonth ]
                                                                              expiryYear:[NSString stringWithFormat:@"20%lu", (unsigned long)cardParams.expYear ]
                                                                                     CVV:cardParams.cvc
                                                                                   error:&error];
    if (error) {
        // See error.code (OPPErrorCode) and error.localizedDescription to identify the reason of failure
        NSLog(@"validateShopperDetails ERROR %@",error.localizedDescription);
    }
    return params;
}



-(void)submitTransaction:(NSString*)checkoutID :(STPCardParams *)cardParams
{
    OPPTransaction *transaction = [OPPTransaction transactionWithPaymentParams:[self validateShopperDetails:checkoutID :(STPCardParams *)cardParams ]];
    
    [self.provider submitTransaction:transaction completionHandler:^(OPPTransaction * _Nonnull transaction, NSError * _Nullable error) {
        if (transaction.type == OPPTransactionTypeAsynchronous) {
            // Open transaction.redirectURL in Safari browser to complete the transaction
        }  else if (transaction.type == OPPTransactionTypeSynchronous) {
            // Send request to your server to obtain transaction status
            NSLog(@"Send request to your server to obtain transaction status");
            [self requestStatus:checkoutID];

        } else {
            // Handle the error
                NSLog(@"submitTransaction error> %@",error);
        }
    }];
}


-(void)requestStatus :(NSString*)checkoutID
{
//    /payments/${userId}/${paymentId}/peach/status`
    FIRDatabaseReference *  ref = [[FIRDatabase database] reference];
    FIRUser *user = [FIRAuth auth].currentUser;
    
     [[[[[[ref child:@"payments"] child:user.uid]  child:uuid] child:@"peach"] child:@"status"]  setValue:checkoutID withCompletionBlock:^(NSError * _Nullable error, FIRDatabaseReference * _Nonnull ref) {
        if (error)
            [self showError:error];
    }];
    
    

    [[[[[[ref child:@"payments"] child:user.uid]  child:uuid] child:@"peach"] child:@"status"] observeEventType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
        NSLog(@"snapshot.value %@",snapshot.value);
        if (![snapshot.value isKindOfClass:[NSNull class]])
        {
            // [self peachSubmit:cardParams
            //                 :snapshot.value];
            
           // [self submitTransaction:snapshot.value :cardParams];
            
        }
    } withCancelBlock:^(NSError * _Nonnull error) {
        NSLog(@"%@", error.localizedDescription);
        [self showError:error];
    }];
}







-(void)submitPressed
{
    [spinner startAnimating];
    uuid = [[NSUUID UUID] UUIDString];
    cardParams = [[STPCardParams alloc] init];
   
    cardParams.number = _chargeTextField.cardNumber;
    cardParams.expMonth = _chargeTextField.expirationMonth;
    cardParams.expYear = _chargeTextField.expirationYear;
    cardParams.cvc = _chargeTextField.cvc;
    
    
    [[STPAPIClient sharedClient] createTokenWithCard:cardParams completion:^(STPToken *token, NSError *error) {
        if (token == nil || error != nil) {
             [self showError:error];
            return;
        }
        FIRUser *user = [FIRAuth auth].currentUser;
        NSLog(@"token>>> %@",token);
        NSLog(@"user.uid %@",user.uid);
        FIRDatabaseReference *  ref = [[FIRDatabase database] reference];
        
        [[[[ref child:@"users"] child:user.uid] child:@"balance"] setValue:[NSNumber numberWithDouble:0] withCompletionBlock:^(NSError * _Nullable error, FIRDatabaseReference * _Nonnull ref) {
            if (error)
                [self showError:error];
        }];
        
        NSString *key = [NSString stringWithFormat:@"%@/%@", user.uid,uuid];
        NSDictionary *post = @{@"token": token.tokenId,
                               @"amount": [NSNumber numberWithDouble:5000]
                               };
       
        NSDictionary *childUpdates = @{[@"/payments/" stringByAppendingString:key]: post};
        [ref updateChildValues:childUpdates];
        
        [[[[[ref child:@"payments"] child:user.uid]  child:uuid] child:@"error"] observeEventType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
            NSLog(@"snapshot.value %@",snapshot.value);
            if (![snapshot.value isKindOfClass:[NSNull class]])
            {
                [self showDeclined:snapshot.value];
            }
        } withCancelBlock:^(NSError * _Nonnull error) {
            NSLog(@"%@", error.localizedDescription);
            [self showError:error];
        }];
        
        [[[[[[ref child:@"payments"] child:user.uid]  child:uuid] child:@"charge"] child:@"status"] observeEventType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
            NSLog(@"snapshot.value %@",snapshot.value);
            if (![snapshot.value isKindOfClass:[NSNull class]])
            {
                if ([@"succeeded" isEqualToString:snapshot.value])
                {
                    [self showSuccess];
                }
            }
        } withCancelBlock:^(NSError * _Nonnull error) {
            NSLog(@"%@", error.localizedDescription);
            [self showError:error];
        }];
        
        
        [[[[[[ref child:@"payments"] child:user.uid]  child:uuid] child:@"peach"] child:@"id"] observeEventType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
            NSLog(@"snapshot.value %@",snapshot.value);
            if (![snapshot.value isKindOfClass:[NSNull class]])
            {
               // [self peachSubmit:cardParams
                //                 :snapshot.value];
                
                [self submitTransaction:snapshot.value :cardParams];

            }
        } withCancelBlock:^(NSError * _Nonnull error) {
            NSLog(@"%@", error.localizedDescription);
            [self showError:error];
        }];
        
        
    }];
}




-(void)showDeclined:(NSString*)declinedMessage
{
    [spinner stopAnimating];
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Credit Card" message:declinedMessage delegate:self cancelButtonTitle:nil otherButtonTitles: @"OK",nil];
    [alert show];
}


-(void)showSuccess
{
    [spinner stopAnimating];
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Credit Card" message:@"Success" delegate:self cancelButtonTitle:nil otherButtonTitles: @"OK",nil];
    [alert show];
}


-(void)showError:(NSError*)error
{
    [spinner stopAnimating];
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Credit Card" message:error.localizedDescription delegate:self cancelButtonTitle:nil otherButtonTitles: @"OK",nil];
    [alert show];
}





//    OPPTransaction *transaction = [OPPTransaction transactionWithPaymentParams:params];
//
//    [self.provider submitTransaction:transaction completionHandler:^(OPPTransaction * _Nonnull transaction, NSError * _Nullable error) {
//        if (transaction.type == OPPTransactionTypeAsynchronous) {
//            // Open transaction.redirectURL in Safari browser to complete the transaction
//        }  else if (transaction.type == OPPTransactionTypeSynchronous) {
//            // Send request to your server to obtain transaction status
//        } else {
//            // Handle the error
//        }
//    }];


//-(void)peachSubmit:(STPCardParams *)cardParams :(NSString*)peachId
//{
////    self.provider = [OPPPaymentProvider paymentProviderWithMode:OPPProviderModeTest];
//
//    NSString *applicationIdentifier = @"com.easeAppSoftware.StripeTest";        // Default value
//    NSString *profileToken = @"5644a34583fc49da87892843aa8fb27b";
//
//      self.provider = [PWPaymentProvider getProviderWithApplicationId: applicationIdentifier profileToken:peachId];
//
//    NSError *error;
//    PWPaymentParams *ccParams = [_provider.paymentParamsFactory
//                                 createCreditCardPaymentParamsWithAmount:5.0
//                                 currency:EUR
//                                 subject:@"A test charge"
//                                 ccNumber:cardParams.number
//                                 name:@"Ray"
//                                 expiryYear:@"2019"
//                                 expiryMonth:[NSString stringWithFormat:@"%lu", (unsigned long)cardParams.expMonth ]
//                                 CVV:cardParams.cvc
//                                 latitude:0
//                                 longitude:0
//                                 horizontalAccuracy:0
//                                 error:&error];
//
//    NSLog(@"ccParams %@",ccParams);
//    NSLog(@"error> %@",error);
//
//    [_provider queryTransactionStatusForTransaction:peachId onSuccessfulQuery:^(PWTransactionStatus lastSuccess) {
//        NSLog(@"lastSuccess %d",lastSuccess);
//    } onQueryFailure:^(NSError *error) {
//        NSLog(@"error>> %@",error);
//
//    }];
//
//
//
//}



@end
