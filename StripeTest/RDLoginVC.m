//
//  MDLoginVC.m
//  Shop&Deliver
//
//  Created by Ray de Rose on 2017/03/21.
//  Copyright © 2017 Ray de Rose. All rights reserved.
//

#import "RDLoginVC.h"
//#import "RDEmailLoginVC.h"
//#import "Constants.h"
//#import "RDPersistenceManager.h"
//#import "RDRegisterVC.h"
//#import <Crashlytics/Crashlytics.h>
//#import "UIView+Animation.h"
//#import "RDForgottonPasswordVC.h"
#import "RDActivityButton.h"
//#import "UITextField+ClearButton.h"
//#import "UIImage+REFrostedViewController.h"
@import FirebaseAnalytics;
//#import "RDErrorManager.h"

#import <Stripe/Stripe.h>

#import "ViewController.h"



#import <Firebase/Firebase.h>

@import GoogleSignIn;

# define labelHeight 12.0f

@interface RDLoginVC ()
{
    UIScrollView *slidingView;
    
    //RDActivityButton *loginButton;
    
    UILabel *emailLabel;
    
    UILabel *passwordLabel;
    
    UIView *whiteLine;
    
    UIView *whiteLine2;
    
    NSString *email;
    
    NSString *password;
    
   // RDRegisterVC * registrationVC;
    
    UIView *fakeRegistrationV;
    
    int attempts;
    
    NSString * forgot_password;
    
    NSString * signup;
    
    NSString * source;  // landing_screen, checkout
    
    NSString * successful; // Yes, No
    RDActivityButton *  loginButton;
    
    STPAddCardViewController *addCardViewController ;
}
@end



@implementation RDLoginVC


@synthesize emailTextField;
@synthesize passwordTextField;
@synthesize transitionFrom;
@synthesize image;






- (void)viewDidLoad
{
    [super viewDidLoad];
    [GIDSignIn sharedInstance].delegate = self;
    

    
    
    UIView *darkOverlay =[[UIView alloc]initWithFrame:CGRectMake(0,0, self.view.bounds.size.width, self.view.bounds.size.height)];
    darkOverlay.backgroundColor = [UIColor blackColor];
    darkOverlay.alpha = 0.6;
    [self.view addSubview:darkOverlay];
    self.view.backgroundColor = [UIColor clearColor];
    slidingView = [[UIScrollView alloc] initWithFrame:CGRectMake(0,0, self.view.bounds.size.width, self.view.bounds.size.height)];
    slidingView.backgroundColor = [UIColor clearColor];
    slidingView.delegate = self;
    UIScreen *screen = [UIScreen mainScreen];
    float screenHeight = 100;
    int nextY = 0;
    if (screen.bounds.size.height <= 568.00)
    {
        screenHeight = 20;
    }
    slidingView.contentSize = CGSizeMake(self.view.bounds.size.width,self.view.bounds.size.height-screenHeight);
    [self.view addSubview:slidingView];
    
   // float linePadding = 40;
    float textYspacing = 50;
    
//    email = @"Email address";
//    emailLabel = [[UILabel alloc]initWithFrame:CGRectMake(kContentLeftOffset,nextY,self.view.bounds.size.width  - (2 * kContentLeftOffset), labelHeight)];
//    emailLabel.text = email;
//    emailLabel.textColor = [UIColor whiteColor];
//    emailLabel.font = [UIFont systemFontOfSize:11];
//    emailLabel.textAlignment = NSTextAlignmentCenter;
//    
//    UIView *emailView = [[UIView alloc] initWithFrame:CGRectMake(kContentLeftOffset,nextY,self.view.bounds.size.width  - (2 * kContentLeftOffset), textViewHeight)];
//    [slidingView addSubview:emailView];
//    
//    emailTextField = [[UITextField alloc] initWithFrame:CGRectMake(0,0,self.view.bounds.size.width  - (2 * kContentLeftOffset), textViewHeight)];
//    [emailTextField modifyClearButtonWithImage:[UIImage imageNamed:@"clearTextIcon"]];
//    emailTextField.tag = 1;
//    emailTextField.textColor = [UIColor whiteColor];
//    emailTextField.attributedPlaceholder = [[NSAttributedString alloc] initWithString:@"Email address" attributes:@{NSForegroundColorAttributeName: [UIColor whiteColor]}];
//    emailTextField.textAlignment = NSTextAlignmentCenter;
//    emailTextField.font = [UIFont boldSystemFontOfSize:mediumFontSize];
//    emailTextField.delegate = self;
//    emailTextField.returnKeyType = UIReturnKeyNext;
//    emailTextField.autocorrectionType = UITextAutocorrectionTypeNo;
//    emailTextField.autocapitalizationType = UITextAutocapitalizationTypeNone;
//    emailTextField.keyboardType = UIKeyboardTypeEmailAddress;
//    [emailView addSubview:emailTextField];
//    
//    whiteLine = [[UIView alloc]initWithFrame:CGRectMake(kContentLeftOffset, linePadding +nextY, self.view.bounds.size.width  - (2 * kContentLeftOffset), 1)];
//    whiteLine.backgroundColor = [UIColor lightGrayColor];
//    [slidingView addSubview:whiteLine];
//    
//    nextY +=textYspacing;
//    
//    password = @"Password";
//    passwordLabel = [[UILabel alloc]initWithFrame:CGRectMake(kContentLeftOffset,nextY,self.view.bounds.size.width  - (2 * kContentLeftOffset), labelHeight)];
//    passwordLabel.text = password;
//    passwordLabel.textColor = [UIColor whiteColor];
//    passwordLabel.font = [UIFont systemFontOfSize:11];
//    passwordLabel.textAlignment = NSTextAlignmentCenter;
//    UIView *passwordView = [[UIView alloc] initWithFrame:CGRectMake(kContentLeftOffset,nextY,self.view.bounds.size.width  - (2 * kContentLeftOffset), textViewHeight)];
//    [slidingView addSubview:passwordView];
//    
//    passwordTextField = [[UITextField alloc] initWithFrame:CGRectMake(20,0,self.view.bounds.size.width  - (2 * kContentLeftOffset)-40, textViewHeight)];
//    [passwordTextField modifyClearButtonWithImage:[UIImage imageNamed:@"clearTextIcon"]];
//    passwordTextField.tag = 2;
//    passwordTextField.textColor = [UIColor whiteColor];
//    passwordTextField.font = [UIFont boldSystemFontOfSize:mediumFontSize];
//    passwordTextField.attributedPlaceholder = [[NSAttributedString alloc] initWithString:password attributes:@{NSForegroundColorAttributeName: [UIColor whiteColor]}];
//    passwordTextField.secureTextEntry = YES;
//    passwordTextField.textAlignment = NSTextAlignmentCenter;
//    passwordTextField.keyboardType = UIKeyboardTypeDefault;
//    passwordTextField.autocorrectionType = UITextAutocorrectionTypeNo;
//    passwordTextField.autocapitalizationType = UITextAutocapitalizationTypeNone;
//    passwordTextField.delegate = self;
//    [passwordView addSubview:passwordTextField];
//    
//    whiteLine2 = [[UIView alloc]initWithFrame:CGRectMake(kContentLeftOffset, linePadding +nextY, self.view.bounds.size.width  - (2 * kContentLeftOffset), 1)];
//    whiteLine2.backgroundColor = [UIColor lightGrayColor];
//    [slidingView addSubview:whiteLine2];
    
    nextY +=textYspacing;
    nextY +=textYspacing;
    
//    UIView* blackSignOutBackground = [[UIView alloc]initWithFrame:CGRectMake(kContentLeftOffset,nextY ,self.view.bounds.size.width - (2 * kContentLeftOffset), textViewHeight)];
//    blackSignOutBackground.backgroundColor = [UIColor blackColor];
//    blackSignOutBackground.alpha = 0.1f;
//    blackSignOutBackground.layer.cornerRadius = textViewHeight/2;
//    blackSignOutBackground.layer.masksToBounds = YES;
    //[slidingView addSubview:blackSignOutBackground];
    
    
//    FBSDKLoginButton *fbButton = [[FBSDKLoginButton alloc] init];
//    fbButton.delegate = self;
//    fbButton.frame = CGRectMake(20,nextY ,self.view.bounds.size.width - (2 * 20), 50);
//    fbButton.readPermissions = @[@"public_profile", @"email", @"user_friends",@"user_likes"];
//    [self.view addSubview:fbButton];
//
//    nextY +=textYspacing+20;

   
    GIDSignInButton *signInButton = [[GIDSignInButton alloc]init];
    signInButton.frame = CGRectMake(20,nextY ,self.view.bounds.size.width - (2 * 20), 50);
 
    [self.view addSubview:signInButton];
    
    nextY += 80;
    
//   loginButton = [RDActivityButton buttonWithType:UIButtonTypeCustom];
//    loginButton.frame = CGRectMake(20,nextY ,self.view.bounds.size.width - (2 * 20), 50);
//    //loginButton.layer.cornerRadius = textViewHeight/2;
//    loginButton.layer.masksToBounds = YES;
//    loginButton.layer.borderColor = [UIColor lightGrayColor].CGColor;
//    loginButton.layer.borderWidth = 1;
//    [loginButton setTitle:@"Log in with email"  forState:UIControlStateNormal];
//    [loginButton setTitle:@"Log in with email"  forState:UIControlStateSelected];
//    [loginButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
//    [loginButton setTitleColor:[UIColor grayColor] forState:UIControlStateHighlighted];
//    [loginButton setTitleColor:[UIColor grayColor] forState:UIControlStateSelected];
//   // [loginButton setBackgroundColor:[UIColor lightGrayColor] forState:UIControlStateHighlighted];
//    loginButton.titleLabel.font = [UIFont systemFontOfSize:14];
//    loginButton.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin;
//    [loginButton addTarget:self action:@selector(loginButtonPressed) forControlEvents:UIControlEventTouchUpInside];
//    [slidingView addSubview:loginButton];
//
//    nextY +=textYspacing;
//    if (screen.bounds.size.height != 480.00)
//        nextY +=textYspacing;
//
//    UIButton * forgotenButton = [UIButton buttonWithType:UIButtonTypeCustom];
//    forgotenButton.frame = CGRectMake(self.view.bounds.size.width/2 - 70,nextY ,140, 20);
//    [forgotenButton setTitle:@"Forgot password?"  forState:UIControlStateNormal];
//    [forgotenButton setTitleColor:[UIColor lightGrayColor] forState:UIControlStateNormal];
//    forgotenButton.titleLabel.font = [UIFont boldSystemFontOfSize:15];
//    forgotenButton.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin;
//    [forgotenButton addTarget:self action:@selector(fadeInForgotten) forControlEvents:UIControlEventTouchUpInside];
//    [slidingView addSubview:forgotenButton];
//
//    nextY += 80;
//
//    //    UIView *line = [[UIView alloc]initWithFrame:CGRectMake((self.view.bounds.size.width/2)-15,nextY,30,2)];
//    //    line.backgroundColor = [UIColor whiteColor];
//    //    [slidingView addSubview:line];
//    //
////    nextY += 40;
//
////    UILabel *  newToMrDLabel = [[UILabel alloc]initWithFrame:CGRectMake(kContentLeftOffset,nextY-20 ,self.view.bounds.size.width - (2 * kContentLeftOffset), 50)];
////    newToMrDLabel.text = @"New to the e2me App?";
////    newToMrDLabel.textColor = [UIColor lightGrayColor];
////    newToMrDLabel.font = [UIFont systemFontOfSize:12];
////    newToMrDLabel.textAlignment = NSTextAlignmentCenter;
////    [slidingView addSubview:newToMrDLabel];
//
//    _signInButton = [UIButton buttonWithType:UIButtonTypeCustom];
//    _signInButton.frame = CGRectMake(20,nextY+20 ,self.view.bounds.size.width - (2 * 20), 50);
//    _signInButton.userInteractionEnabled = YES;
//    [_signInButton setTitle:@"Sign up" forState:UIControlStateNormal];
//    [_signInButton setTitleColor:[UIColor darkGrayColor] forState:UIControlStateHighlighted];
//    [_signInButton setTitleColor:[UIColor grayColor] forState:UIControlStateSelected];
//    _signInButton.titleLabel.font = [UIFont boldSystemFontOfSize:15];
//    _signInButton.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin;
//    [_signInButton addTarget:self action:@selector(fadeInSignUp) forControlEvents:UIControlEventTouchUpInside];
//    [slidingView addSubview:_signInButton];
    
    UIButton *closeButton2 = [UIButton buttonWithType:UIButtonTypeCustom];
    closeButton2.frame = CGRectMake(screen.bounds.size.width-50, 5, 50.0, 50.0);
    closeButton2.userInteractionEnabled = YES;
    [closeButton2 setImage:[UIImage imageNamed:@"closeIconWhite"] forState:UIControlStateNormal];
    closeButton2.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin;
    [closeButton2 addTarget:self action:@selector(popThisView) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:closeButton2];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardDidShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
    
    forgot_password = @"NO";
    signup = @"NO";
    source= @"landing_screen";
    successful = @"";
   // [self logFireBaseEvent:@"view_log_in_screen"];
    
    [GIDSignIn sharedInstance].uiDelegate = self;
   // [[GIDSignIn sharedInstance] signIn];
    
   
    
}





-(void)loginButtonDidLogOut:(FBSDKLoginButton *)loginButt
{
    [[NSUserDefaults standardUserDefaults]removeObjectForKey:@"email"];
    [[NSUserDefaults standardUserDefaults]removeObjectForKey:@"password"];
    [[NSUserDefaults standardUserDefaults]synchronize];
    
    [self popThisView];
  
    [loginButton stopIndicator];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"userLogedInFromLanding" object:nil];

}









- (void)signIn:(GIDSignIn *)signIn
didSignInForUser:(GIDGoogleUser *)user
     withError:(NSError *)error {
    // ...
    if (error == nil) {
        GIDAuthentication *authentication = user.authentication;
        FIRAuthCredential *credential =
        [FIRGoogleAuthProvider credentialWithIDToken:authentication.idToken
                                         accessToken:authentication.accessToken];
        
        
        [[FIRAuth auth] signInWithCredential:credential
                                  completion:^(FIRUser *user, NSError *error) {
                                      [self saveLogin:user];
                                      if (error) {
                                          NSLog(@"[error userInfo] %@",[error userInfo]);
                                          NSDictionary * userInfo = [error userInfo];
                                          
                                          UIAlertView *alert = [[UIAlertView alloc] initWithTitle:userInfo[@"error_name"]
                                                                                          message:[error localizedDescription]
                                                                                         delegate:self
                                                                                cancelButtonTitle:nil
                                                                                otherButtonTitles: @"OK", nil];
                                          alert.delegate = self;
                                          [alert show];
                                          
                                         // [RDErrorManager logErrorToSlackWithTitle:userInfo[@"error_name"]  message:[error localizedDescription]];
                                          return;
                                      }
                                      else
                                      {

                                          // Present add card view controller
                                          ViewController *addCardViewController = [[ViewController alloc] init];
                                          UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:addCardViewController];
                                          [self presentViewController:navigationController animated:YES completion:nil];
                                      }
                                  }];
        // ...
    } else {
        // ...
    }
}


#pragma mark STPAddCardViewControllerDelegate

- (void)addCardViewControllerDidCancel:(STPAddCardViewController *)addCardViewController {
    // Dismiss add card view controller
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)addCardViewController:(STPAddCardViewController *)addCardViewController didCreateToken:(STPToken *)token completion:(STPErrorBlock)completion {
    [self submitTokenToBackend:token completion:^(NSError *error) {
        if (error) {
            // Show error in add card view controller
            completion(error);
        }
        else {
            // Notify add card view controller that token creation was handled successfully
            completion(nil);
            
            // Dismiss add card view controller
            [self dismissViewControllerAnimated:YES completion:nil];
        }
    }];
}

-(void)submitTokenToBackend:(STPToken*)token  completion:(void (^ __nullable)(NSError *error))error
{
//    uuid = [[NSUUID UUID] UUIDString];
//    STPCardParams *cardParams = [[STPCardParams alloc] init];
//    cardParams.number = chargeTextField.cardNumber;
//    cardParams.expMonth = _chargeTextField.expirationMonth;
//    cardParams.expYear = _chargeTextField.expirationYear;
//    cardParams.cvc = _chargeTextField.cvc;
//    [[STPAPIClient sharedClient] createTokenWithCard:cardParams completion:^(STPToken *token, NSError *error) {
//        if (token == nil || error != nil) {
//            // Present error to user...
//            return;
//        }
//        FIRUser *user = [FIRAuth auth].currentUser;
//        
//        NSLog(@"token>>> %@",token);
//        NSLog(@"user.uid %@",user.uid);
//        FIRDatabaseReference *  ref = [[FIRDatabase database] reference];
//        // Add a payment source (card) for a user by writing a stripe payment source token to Realtime database
//        //        exports.addPaymentSource = functions.database.ref('/stripe_customers/{userId}/sources/{pushId}/token').onWrite(event => {
//        //     [[[[[ref child:@"stripe_customers"] child:user.uid]   child:@"sources"] child:uuid] setValue:token.tokenId withCompletionBlock:^(NSError * _Nullable error, FIRDatabaseReference * _Nonnull ref) {
//        
//        [[[[[[ref child:@"stripe_customers"] child:user.uid]   child:@"sources"] child:uuid] child:@"token"]setValue:token.tokenId withCompletionBlock:^(NSError * _Nullable error, FIRDatabaseReference * _Nonnull ref) {
//            NSLog(@"ref %@",ref);
//            if (!error) {
//                [self chargeCreditCard];
//            }
//            else
//            {
//                RDLog(@"error %@",error.localizedDescription);
//                UIAlertView *alert =
//                [[UIAlertView alloc] initWithTitle:@"Credit Card" message:error.localizedDescription delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles: @"Submit",nil];
//                [alert show];
//            }
//        }];
//    }];
}





-(void)saveLogin:(FIRUser*)user
{
    attempts ++;
    [self popThisView];
    [[NSUserDefaults standardUserDefaults]setObject:user.email forKey:@"email"];
    if (!user.email)
    {
            [[NSUserDefaults standardUserDefaults]setObject:user.displayName forKey:@"email"];
    }
    
    
    
    [[NSUserDefaults standardUserDefaults]synchronize];
    [loginButton stopIndicator];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"userLogedInFromLanding" object:nil];
}



- (void) logUser  {
    // TODO: Use the current user's information
    // You can call any combination of these three methods
   // [CrashlyticsKit setUserIdentifier:@"12345"];
   // [CrashlyticsKit setUserEmail:[[NSUserDefaults standardUserDefaults] objectForKey:@"email"]];
    //[CrashlyticsKit setUserName:@"Test User"];
}




-(void)getRegistrationNotication:(NSNotification *)notification
{
    [self popThisView];
}



-(void)popThisView
{
    CATransition* transition = [CATransition animation];
    transition.duration = 0.3;
    transition.type = kCATransitionFade;
    [self.navigationController.view.layer addAnimation:transition forKey:kCATransition];
    [self.navigationController popViewControllerAnimated:NO];
}




- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
}



-(void)loginUser
{
    [[FIRAuth auth] signInWithEmail:emailTextField.text
                           password:passwordTextField.text
                         completion:^(FIRUser *user, NSError *error) {
                            // [loginButton stopIndicator];
                             if (user) {
                                 
                                 [[NSUserDefaults standardUserDefaults]setObject:passwordTextField.text forKey:@"password"];
                                 [[NSUserDefaults standardUserDefaults]setObject:emailTextField.text forKey:@"email"];
                                 [[NSUserDefaults standardUserDefaults]synchronize];
                                 
                                 attempts ++;
                                 [self popThisView];
                             }
                             else
                                 if (error) {
                                     
                                     
                                     NSLog(@"[error userInfo] %@",[error userInfo]);
                                     NSDictionary * userInfo = [error userInfo];
                                     
                                     UIAlertView *alert = [[UIAlertView alloc] initWithTitle:userInfo[@"error_name"]
                                                                                     message:[error localizedDescription]
                                                                                    delegate:self
                                                                           cancelButtonTitle:nil
                                                                           otherButtonTitles: @"OK", nil];
                                     alert.delegate = self;
                                     [alert show];
                                     
                                     //[RDErrorManager logErrorToSlackWithTitle:userInfo[@"error_name"]  message:[error localizedDescription]];

                                 }
                         }];
}



#pragma mark - MDErrorManagerDelegate methods

-(void)fadeInSignUpFromAlert
{
    [self fadeInSignUp];
}



-(void)fadeInForgottenFromAlert
{
    [self fadeInForgotten];
}


#pragma mark -



-(void)fadeInSignUp
{
//    BOOL pop = NO;
//    for (UIViewController * viewControll in self.navigationController.viewControllers)
//    {
//        NSLog(@"viewControll %@",viewControll);
//
//        if ([viewControll isKindOfClass:[RDRegisterVC class]])
//        {
//            pop = YES;
//            break;
//        }
//    }
//    if (pop)
//    {
//        [self popThisView];
//    }
//    else
//    {
//        signup = @"YES";
//        RDRegisterVC * registerVC = [[RDRegisterVC alloc]init];
//        registerVC.fromLogin = @"YES";
//        CATransition* transition = [CATransition animation];
//        transition.duration = 0.3;
//        transition.type = kCATransitionFade;
//        [self.navigationController.view.layer addAnimation:transition forKey:kCATransition];
//        [self.navigationController pushViewController:registerVC animated:NO];
//    }
}


-(void)fadeInForgotten
{
//    forgot_password = @"YES";
//    RDForgottonPasswordVC* forgottonPasswordVC = [[RDForgottonPasswordVC alloc]init];
//
//    CATransition* transition = [CATransition animation];
//    transition.duration = 0.3;
//    transition.type = kCATransitionFade;
//    [self.navigationController.view.layer addAnimation:transition forKey:kCATransition];
//    [self.navigationController pushViewController:forgottonPasswordVC animated:NO];
//
//    if ([[RDPersistenceManager sharedPersistenceManager] isValidEmail:emailTextField.text]) {
//        forgottonPasswordVC.currentEmail = emailTextField.text;
//    }
}




-(void)logFireBaseEvent:(NSString*)event
{
    if([transitionFrom isEqualToString:@"MDCartVC"])
        source = @"checkout";
    else
        if([transitionFrom isEqualToString:@"MDProfileSliderVC"])
            source = @"side_nav";
    [FIRAnalytics logEventWithName:event parameters:@{@"source": source}];
}


-(BOOL)prefersStatusBarHidden
{
    return YES;
}



-(void)viewWillLayoutSubviews
{
    [super.view layoutIfNeeded];
    [self.view layoutIfNeeded];
}



-(void)subscribeToPushWithUserId :(int)useId
{
    
    if (useId>0)
    {
        NSString * userId = [NSString stringWithFormat:@"user_%d",useId];
        NSLog(@"                                                                                         SUBSCRIBING %@",userId);
        if( [[[NSUserDefaults standardUserDefaults] objectForKey:@"promNotificationsOff" ]boolValue]!=YES)
            [self performSelector:@selector(subscribeToMarketingAterDelay) withObject:nil afterDelay:3];
    }
}



-(void)subscribeToMarketingAterDelay
{
    NSLog(@"                                                                                         SUBSCRIBING FIREBASE marketing");
    // [[FIRMessaging messaging] subscribeToTopic:@"/topics/marketing"];
    [[NSUserDefaults standardUserDefaults] setObject:@YES forKey:@"promNotificationsOn"];
    [[NSUserDefaults standardUserDefaults] synchronize];
}








- (BOOL)textFieldShouldEndEditing:(UITextView *)textView;
{
    return YES;
}



- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
    UIScreen *screen = [UIScreen mainScreen];
    NSLog(@"screen.bounds.size.height %f",screen.bounds.size.height);
    if (screen.bounds.size.height < 667 && textField.tag==1)
    {
        CGPoint newScrollOrigin = CGPointMake( 0.0,  50);
        [slidingView setContentOffset:newScrollOrigin animated:YES];
    }
    else
    {
        if (screen.bounds.size.height < 667)
        {
            CGPoint newScrollOrigin = CGPointMake( 0.0,  100);
            [slidingView setContentOffset:newScrollOrigin animated:YES];
        }
    }
    return YES;
}



-(void)loginButtonPressed
{
    
    
    RDLoginVC* loginVC = [[RDLoginVC alloc]init];
    
    CATransition* transition = [CATransition animation];
    transition.duration = 0.3;
    transition.type = kCATransitionFade;
    [self.navigationController.view.layer addAnimation:transition forKey:kCATransition];
    [self.navigationController pushViewController:loginVC animated:NO];
        
        [self loginUser];

}




- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}




-(BOOL)textFieldShouldReturn:(UITextField*)textField
{
    UIScreen *screen = [UIScreen mainScreen];
    
    if ( textField.tag==1)
    {
        if (screen.bounds.size.height < 667 )
        {
            CGPoint newScrollOrigin = CGPointMake( 0.0,  100);
            [slidingView setContentOffset:newScrollOrigin animated:YES];
        }
        [passwordTextField becomeFirstResponder];
    }
    else
    {
        [textField resignFirstResponder];
    }
    return NO;
}


- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView
{
    [passwordTextField resignFirstResponder];
    [emailTextField resignFirstResponder];
}


- (void)keyboardWillShow:(NSNotification *)notification {
    slidingView.frame =  CGRectMake(0, 15, self.view.frame.size.width, self.view.frame.size.height-218);
}



- (void)keyboardWillHide:(NSNotification *)notification
{
    slidingView.frame =  CGRectMake(0,15, self.view.bounds.size.width, self.view.bounds.size.height);
}



- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
//    if ( textField.tag == 1)
//    {
//        whiteLine.backgroundColor = [UIColor lightGrayColor];
//        emailLabel.text = email;
//        emailLabel.textColor = [UIColor whiteColor];
//        
//        if (range.length == -1 && range.location == -1) {
//            [emailLabel removeWithZoomOutAnimation:0.6 option:UIViewAnimationOptionShowHideTransitionViews];
//        } else {
//            if (textField.text.length==0)
//            {
//                if (emailLabel.frame.size.height== labelHeight)
//                    [slidingView addSubviewWithZoomInAnimation:emailLabel duration:0.6 option:UIViewAnimationOptionShowHideTransitionViews];
//                else
//                    [slidingView zoomOutAnimation:emailLabel duration:0.6 option:UIViewAnimationOptionShowHideTransitionViews];
//            }
//            else
//                if ( textField.text.length==1&& [string isEqualToString:@""] )
//                    [emailLabel removeWithZoomOutAnimation:0.6 option:UIViewAnimationOptionShowHideTransitionViews];
//        }
//    }
//    else if ( textField.tag == 2)
//    {
//        whiteLine2.backgroundColor = [UIColor lightGrayColor];
//        passwordLabel.text =  password;
//        passwordLabel.textColor = [UIColor whiteColor];
//        
//        if (range.length == -1 && range.location == -1) {
//            [passwordLabel removeWithZoomOutAnimation:0.6 option:UIViewAnimationOptionShowHideTransitionViews];
//        } else {
//            if ( textField.text.length==0 )
//            {
//                if (passwordLabel.frame.size.height== labelHeight)
//                    [slidingView addSubviewWithZoomInAnimation:passwordLabel duration:0.6 option:UIViewAnimationOptionShowHideTransitionViews];
//                else
//                    [slidingView zoomOutAnimation:passwordLabel duration:0.6 option:UIViewAnimationOptionShowHideTransitionViews];
//            }
//            else
//                if ( textField.text.length==1  && [string isEqualToString:@""] )
//                    [passwordLabel removeWithZoomOutAnimation:0.6 option:UIViewAnimationOptionShowHideTransitionViews];
//        }
//    }
    return YES;
}




- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self  name:UIKeyboardDidShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self  name:UIKeyboardWillHideNotification object:nil];
}





@end
