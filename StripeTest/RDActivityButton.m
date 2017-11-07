//
//  MDActivityButton.m
//  MrDelivery
//
//  Created by Cavan O'Connor on 2016/04/13.
//  Copyright © 2016 Mr Delivery. All rights reserved.
//

#import "RDActivityButton.h"

@implementation RDActivityButton {
    UIActivityIndicatorView *indicator;
}

+ (instancetype)buttonWithType:(UIButtonType)buttonType {
    RDActivityButton *activityButton = [super buttonWithType:buttonType];
    return activityButton;
}

- (void)addIndicator {
    [self addIndicatorWithType:UIActivityIndicatorViewStyleWhite];
}

- (void)addIndicatorWithType:(UIActivityIndicatorViewStyle)type {
    if (!indicator) {
        indicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:type];
        indicator.hidesWhenStopped = YES;
    }
    
    CGFloat halfButtonHeight = self.bounds.size.height / 2;
    CGFloat buttonWidth = self.bounds.size.width;
    indicator.center = CGPointMake(buttonWidth - halfButtonHeight , halfButtonHeight);
    [self addSubview:indicator];
    [indicator startAnimating];
}

- (void)stopIndicator {
    if (indicator) {
        [indicator stopAnimating];
    }
}

@end
