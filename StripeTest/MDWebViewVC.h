//
//  MDWebViewVC.h
//  MrDelivery
//
//  Created by Ray de Rose on 2017/10/31.
//  Copyright © 2017 Mr Delivery. All rights reserved.
//

#import <UIKit/UIKit.h>
//#import "NJKWebViewProgress.h"
//#import "MDMenuNavigationBarView.h"
//#import "MDAnouncement.h"


@interface MDWebViewVC : UIViewController <UIWebViewDelegate>//,NJKWebViewProgressDelegate,MenuNavigationBarDelegate>


//@property (nonatomic, strong) MDMenuNavigationBarView *navigationHeader;


- (instancetype)initWithUrl:(NSURL*)url;


@end
