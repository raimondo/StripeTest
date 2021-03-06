//
//  AppDelegate.m
//  StripeTest
//
//  Created by Ray de Rose on 2017/11/07.
//  Copyright © 2017 Ray de Rose. All rights reserved.
//

#import "AppDelegate.h"

#import "RDLoginVC.h"
#import <Firebase/Firebase.h>
@import FirebaseInstanceID;
@import GoogleSignIn;
#import <Stripe/Stripe.h>
#import "ViewController.h"



@interface AppDelegate ()

@end

@implementation AppDelegate
{
    UINavigationController *navVC ;
    UIViewController * vC;
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
     [FIRApp configure];
    [GIDSignIn sharedInstance].clientID = [FIRApp defaultApp].options.clientID;
    [[STPPaymentConfiguration sharedConfiguration] setPublishableKey:@"pk_test_MmEZXkddStGFJtMRahNDUUz6"];
    
    
//    if (   ! [[NSUserDefaults standardUserDefaults] objectForKey:@"email"])
//    {
//          vC = [[RDLoginVC alloc]init];
//    }
//    else
//    {
       vC = [[ViewController alloc]init];
   // }
    navVC = [[UINavigationController alloc]initWithRootViewController:vC];
    self.window.rootViewController = navVC;
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary *)options {
    
    NSLog(@"url.scheme %@",url.scheme);
    if ([url.scheme caseInsensitiveCompare:@"com.easeAppSoftware.StripeTest.payments"] == NSOrderedSame) {
        // send notification to get payment status
        
      
        [navVC popToViewController:vC animated:YES];
        [[NSNotificationCenter defaultCenter] postNotificationName:@"submitPaymentFrom3ds"
                                                            object:self
                                                          userInfo:nil];
        
        return YES;
    } else {
        return NO;
    }
}


@end
