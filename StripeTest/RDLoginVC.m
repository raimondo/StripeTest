//
//  MDLoginVC.m
//  Shop&Deliver
//
//  Created by Ray de Rose on 2017/03/21.
//  Copyright © 2017 Ray de Rose. All rights reserved.
//

#import "RDLoginVC.h"


@import FirebaseAnalytics;

#import <Stripe/Stripe.h>
#import "ViewController.h"
#import <Firebase/Firebase.h>
@import GoogleSignIn;


@interface RDLoginVC ()
{
    STPAddCardViewController *addCardViewController ;
}
@end



@implementation RDLoginVC


- (void)viewDidLoad
{
    [super viewDidLoad];
    [GIDSignIn sharedInstance].delegate = self;
    [GIDSignIn sharedInstance].uiDelegate = self;

    GIDSignInButton *signInButton = [[GIDSignInButton alloc]init];
    signInButton.frame = CGRectMake(20,200 ,self.view.bounds.size.width - (2 * 20), 50);
    [self.view addSubview:signInButton];
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



-(void)saveLogin:(FIRUser*)user
{
    [[NSUserDefaults standardUserDefaults]setObject:user.email forKey:@"email"];
    if (!user.email)
    {
            [[NSUserDefaults standardUserDefaults]setObject:user.displayName forKey:@"email"];
    }
    [[NSUserDefaults standardUserDefaults]synchronize];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"userLogedInFromLanding" object:nil];
}




- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
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


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}




@end
