//
//  MDActivityButton.h
//  MrDelivery
//
//  Created by Cavan O'Connor on 2016/04/13.
//  Copyright © 2016 Mr Delivery. All rights reserved.
//

#import <UIKit/UIKit.h>
//#import "UIButton+BackgroundColor.h"

@interface RDActivityButton : UIButton

+ (instancetype)buttonWithType:(UIButtonType)buttonType;

- (void)addIndicator;
- (void)addIndicatorWithType:(UIActivityIndicatorViewStyle)type;
- (void)stopIndicator;

@end
