//
//  MDLoginVC.h
//  Shop&Deliver
//
//  Created by Ray de Rose on 2017/03/21.
//  Copyright © 2017 Ray de Rose. All rights reserved.
//

#import <UIKit/UIKit.h>
@import GoogleSignIn;
#import <FBSDKLoginKit/FBSDKLoginKit.h>


@interface RDLoginVC : UIViewController <UITextViewDelegate,UITextFieldDelegate,UIScrollViewDelegate,GIDSignInUIDelegate,FBSDKLoginButtonDelegate>
{
    UITextField *emailTextField;
    
    UITextField *passwordTextField;
    
    
    
    NSString *transitionFrom;
    
    UIImage * image;
    
}

@property (nonatomic,strong) UITextField *emailTextField;

@property (nonatomic,strong) UITextField *passwordTextField;



@property (nonatomic,strong) NSString *transitionFrom;

@property (nonatomic,strong) UIButton * signInButton;

@property (nonatomic,strong) UIImage * image;

@end









