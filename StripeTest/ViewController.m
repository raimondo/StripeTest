//
//  ViewController.m
//  StripeTest
//
//  Created by Ray de Rose on 2017/11/07.
//  Copyright © 2017 Ray de Rose. All rights reserved.
//

#import "ViewController.h"
#import <Firebase/Firebase.h>



@interface ViewController ()
{
    BOOL chargeButtonAdded;
    UIActivityIndicatorView * spinner;
    NSString *uuid;
    UIButton *  chargeButton;
}

@property(nonatomic,strong) STPPaymentCardTextField * chargeTextField;


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


-(void)submitPressed
{
    [spinner startAnimating];
    uuid = [[NSUUID UUID] UUIDString];
    STPCardParams *cardParams = [[STPCardParams alloc] init];
    cardParams.number = _chargeTextField.cardNumber;
    cardParams.expMonth = _chargeTextField.expirationMonth;
    cardParams.expYear = _chargeTextField.expirationYear;
    cardParams.cvc = _chargeTextField.cvc;
    
    
    [[STPAPIClient sharedClient] createTokenWithCard:cardParams completion:^(STPToken *token, NSError *error) {
        if (token == nil || error != nil) {
            // Present error to user...
            return;
        }
        FIRUser *user = [FIRAuth auth].currentUser;
        NSLog(@"token>>> %@",token);
        NSLog(@"user.uid %@",user.uid);
        FIRDatabaseReference *  ref = [[FIRDatabase database] reference];
        
        //        exports.addPaymentSource = functions.database.ref('/stripe_customers/{userId}/sources/{pushId}/token').onWrite(event =>
        
        [[[[[[ref child:@"stripe_customers"] child:user.uid]   child:@"sources"] child:uuid] child:@"token"]setValue:token.tokenId withCompletionBlock:^(NSError * _Nullable error, FIRDatabaseReference * _Nonnull ref) {
            NSLog(@"ref %@",ref);
            if (!error) {
                [self chargeCreditCard];
            }
            else
            {
                [self showError:error];
            }
        }];
    }];
}



-(void)chargeCreditCard
{
    FIRUser *user = [FIRAuth auth].currentUser;
    FIRDatabaseReference *  ref = [[FIRDatabase database] reference];
    
    //  exports.createStripeCharge = functions.database.ref('/stripe_customers/{userId}/charges/{id}').onWrite(event => {
    
    [[[[[[ref child:@"stripe_customers"] child: user.uid]   child:@"charges"] child:uuid]child: @"amount"]setValue:[NSNumber numberWithDouble:5000] withCompletionBlock:^(NSError * _Nullable error, FIRDatabaseReference * _Nonnull ref) {
        if (!error) {
            NSLog(@"ref %@",ref);
        }
        else
        {
            [self showError:error];
        }
    }];
    
    [[[[[[ref child:@"stripe_customers"] child:user.uid]   child:@"charges"] child:uuid] child:@"status"] observeEventType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
        NSLog(@"succeeded %@",snapshot.value);
        if ([@"succeeded" isEqualToString:snapshot.value])
        {
            [self showSuccess];
        }
        else
        {
            NSLog(@"%@", snapshot.value);
        }
    } withCancelBlock:^(NSError * _Nonnull error) {
        NSLog(@"%@", error.localizedDescription);
        [self showError:error];
    }];
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



@end
