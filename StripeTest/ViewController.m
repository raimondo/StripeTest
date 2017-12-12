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
#import "MDWebViewVC.h"



@interface ViewController ()
{
    BOOL chargeButtonAdded;
    UIActivityIndicatorView * spinner;
    NSString *uuid;
    UIButton *  chargeButton;
    STPCardParams *cardParams;
    NSString * userID;
    NSString * displayName;;
    
}

@property(nonatomic,strong) STPPaymentCardTextField * chargeTextField;

//@property (strong, nonatomic) PWPaymentProvider *provider;
@property (nonatomic) OPPPaymentProvider *provider;


@end

@implementation ViewController
{
    NSString * tokenString;
    BOOL isSubmitting;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    FIRUser *user = [FIRAuth auth].currentUser;
    
    userID = user.uid;
    if (!userID) {
        userID = @"jqBklLLOV8ch29M1gGRmGBBsGnt2";
        displayName = @"Ray De Rose";
    }
    
    
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
    //    self.provider = [OPPPaymentProvider paymentProviderWithMode:OPPProviderModeLive];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(submitPaymentFrom3ds) name: @"submitPaymentFrom3ds" object:nil];
    
}

-(void)submitPaymentFrom3ds
{
    [self requestStatus:tokenString];
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

-(NSString*)formatMonth:(NSUInteger)mon
{
    int monthInt = (int)mon;
    return  (monthInt <10)?[NSString stringWithFormat:@"0%d",monthInt]:[NSString stringWithFormat:@"%d",monthInt];
}

-(NSString*)formatCardType:(NSString*)number
{
    
    NSString *firstChar =[number substringToIndex:1];
    if ([firstChar isEqualToString:@"4"]) {
        return @"VISA";
    }
    else
        if ([firstChar isEqualToString:@"5"]) {
            return @"MASTER";
        }
        else
            if ([firstChar isEqualToString:@"3"]) {
                return @"AMEX";
            }
    return @"";
    
    
}


-(OPPCardPaymentParams*)validateShopperDetails:(NSString*)checkoutID :(STPCardParams *)cardParams
{
    NSError *error = nil;
    FIRUser *user = [FIRAuth auth].currentUser;
    OPPCardPaymentParams *params = [OPPCardPaymentParams cardPaymentParamsWithCheckoutID:checkoutID
                                                                            paymentBrand:[self formatCardType:cardParams.number]
                                                                                  holder:user.displayName
                                    // holder:displayName
                                                                                  number:cardParams.number
                                                                             expiryMonth:[self formatMonth:cardParams.expMonth]
                                    //                                                                             expiryMonth:[NSString stringWithFormat:@"%lu", (unsigned long)cardParams.expMonth ]
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
        if (transaction.type == OPPTransactionTypeAsynchronous)
        {
            if(![[self.navigationController.viewControllers lastObject]isKindOfClass:[MDWebViewVC class]])
            {
                MDWebViewVC *webVC = [[MDWebViewVC alloc]initWithUrl:transaction.redirectURL];
                [self.navigationController pushViewController:webVC animated:YES];
            }
            
            // Open transaction.redirectURL in Safari browser to complete the transaction
        }  else if (transaction.type == OPPTransactionTypeSynchronous) {
            // Send request to your server to obtain transaction status
            NSLog(@"Send request to your server to obtain transaction status");
            [self requestStatus:checkoutID];
            
        } else {
            // Handle the error
            NSLog(@"submitTransaction error> %@",error);
            [self showError:error];
            isSubmitting = NO;
        }
        
    }];
    
    // }
}


//-(void)requestStatus
//{
//    [self.provider requestCheckoutInfoWithCheckoutID:tokenString completionHandler:^(OPPCheckoutInfo * _Nullable checkoutInfo, NSError * _Nullable error) {
//        if (error) {
//            // Handle error
//        } else {
//            // Use checkoutInfo.resourcePath for getting transaction status
//            NSLog(@"requestStatus checkoutInfo response %@",checkoutInfo);
//        }
//    }];
//}


-(void)requestStatus :(NSString*)checkoutID
{
    FIRDatabaseReference *  ref = [[FIRDatabase database] reference];
    FIRUser *user = [FIRAuth auth].currentUser;
    
    [[[[[ref child:@"payments"] child:userID]  child:uuid] child:@"payment"]   setValue:checkoutID withCompletionBlock:^(NSError * _Nullable error, FIRDatabaseReference * _Nonnull ref) {
        //     [[[[[ref child:@"payments"] child:user.uid]  child:uuid] child:@"payment"]   setValue:checkoutID withCompletionBlock:^(NSError * _Nullable error, FIRDatabaseReference * _Nonnull ref) {
        if (error)
            [self showError:error];
    }];
    
    
    [[[[[ref child:@"payments"] child:userID]  child:uuid] child:@"payment"] observeEventType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
        //    [[[[[ref child:@"payments"] child:user.uid]  child:uuid] child:@"payment"] observeEventType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
        NSLog(@"requestStatus response %@",snapshot.value);
        if ([snapshot.value isKindOfClass:[NSDictionary class]])
        {
            isSubmitting = NO;
            NSDictionary * response = snapshot.value;
            if (response[@"result"]) {
                NSDictionary *result = response[@"result"];
                if (result[@"code"]) {
                    NSString * code = result[@"code"];
                    if ([code isEqualToString:@"000.100.110"]) {
                        [self showSuccess];
                    }else
                        if ([code isEqualToString:@"000.200.000"]) {
                            [self showPending];
                            
                        }
                        else
                            if ([code isEqualToString:@"600.200.500"]|| [code isEqualToString:@"800.100.100"]) {
                                [self showDeclined:result[@"description"]];
                            }
                }
            }
        }
    } withCancelBlock:^(NSError * _Nonnull error) {
        NSLog(@"%@", error.localizedDescription);
        [self showError:error];
    }];
    
    // [self requestStatus];
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
    
    FIRUser *user = [FIRAuth auth].currentUser;
    NSLog(@"user.uid %@",user.uid);
    FIRDatabaseReference *  ref = [[FIRDatabase database] reference];
    
    NSString *key = [NSString stringWithFormat:@"%@/%@", userID,uuid];
    //        NSString *key = [NSString stringWithFormat:@"%@/%@", user.uid,uuid];
    NSDictionary *post = @{
                           @"amount": [NSString stringWithFormat:@"%.2f",500.10]
                           };
    
    NSDictionary *childUpdates = @{[@"/payments/" stringByAppendingString:key]: post};
    [ref updateChildValues:childUpdates];
    
    [[[[[[ref child:@"payments"] child:userID]  child:uuid] child:@"checkout"] child:@"result"] observeEventType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
        //        [[[[[[ref child:@"payments"] child:user.uid]  child:uuid] child:@"checkout"] child:@"result"] observeEventType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
        NSLog(@"submitPressed result response %@",snapshot.value);
        if ([snapshot.value isKindOfClass:[NSDictionary class]])
        {
            NSDictionary * result = snapshot.value;
            if ([result[@"code"] isEqualToString: @"200.300.404"]) {
                [self showDeclined:result[@"description"]];
            }
        }
    } withCancelBlock:^(NSError * _Nonnull error) {
        NSLog(@"%@", error.localizedDescription);
        [self showError:error];
    }];
    
    
    [[[[[[ref child:@"payments"] child:userID]  child:uuid] child:@"checkout"]  child:@"id"] observeEventType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
        
        //        [[[[[[ref child:@"payments"] child:user.uid]  child:uuid] child:@"checkout"]  child:@"id"] observeEventType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
        NSLog(@"submitPressed response %@",snapshot.value);
        if (![snapshot.value isKindOfClass:[NSNull class]])
        {
            // [self peachSubmit:cardParams
            //                 :snapshot.value];
            
            tokenString = snapshot.value;
            
            [self submitTransaction:snapshot.value :cardParams];
            
        }
    } withCancelBlock:^(NSError * _Nonnull error) {
        NSLog(@"%@", error.localizedDescription);
        [self showError:error];
    }];
    
    
    //    }];
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


-(void)showPending
{
    [spinner stopAnimating];
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Credit Card" message:@"Pending" delegate:self cancelButtonTitle:nil otherButtonTitles: @"OK",nil];
    [alert show];
}


-(void)showError:(NSError*)error
{
    [spinner stopAnimating];
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Credit Card" message:error.localizedDescription delegate:self cancelButtonTitle:nil otherButtonTitles: @"OK",nil];
    [alert show];
}








@end
