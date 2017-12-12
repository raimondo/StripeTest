//
//  MDWebViewVC.m
//  MrDelivery
//
//  Created by Ray de Rose on 2017/10/31.
//  Copyright © 2017 Mr Delivery. All rights reserved.
//

#import "MDWebViewVC.h"
//#import "NJKWebViewProgressView.h"
//#import "Constants.h"
//#import "UIColor+MDIAdditions.h"



@interface MDWebViewVC ()
{
    UIWebView *webView;
    UIActivityIndicatorView * spinner;
//    NJKWebViewProgressView *_progressView;
//    NJKWebViewProgress *_progressProxy;
    float statusBar;
}

@property (nonatomic,strong)NSURL * url;
@end



@implementation MDWebViewVC

- (instancetype)initWithUrl:(NSURL*)url
{
    if (!(self = [super init])) { return nil; }
    
    _url = url;
    
    return self;
}



- (void)loadView
{
    [super loadView];
    
    UIScreen *screen = [UIScreen mainScreen];
//    self.navigationHeader = [[MDMenuNavigationBarView alloc] initWithFrame:CGRectMake(0, 0, screen.bounds.size.width, 70) andNavType:NavTypeBackOnly];
//    self.navigationHeader.delegate = self;
//    self.navigationHeader.titleLabel.text = _anouncement.title;
//    self.navigationHeader.backgroundV.backgroundColor = [UIColor colorwithHexString: _anouncement.background_color alpha:1];
//    [self.view addSubview:self.navigationHeader];
//
//
//    _progressProxy = [[NJKWebViewProgress alloc] init]; // instance variable
//    webView.delegate = _progressProxy;
//    _progressProxy.webViewProxyDelegate = self;
//    _progressProxy.progressDelegate = self;
//
//    CGFloat progressBarHeight = 2.f;
//    CGRect barFrame = CGRectMake(0, self.navigationHeader.bounds.size.height - progressBarHeight, self.navigationHeader.bounds.size.width, progressBarHeight);
//    _progressView = [[NJKWebViewProgressView alloc] initWithFrame:barFrame];
//    _progressView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleTopMargin;
//    _progressView.progressBarView.backgroundColor = [UIColor mdi_yellowColor];
//
//    [_progressView setProgress:0.2 animated:YES];
    spinner = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    [spinner setCenter:CGPointMake(self.view.frame.size.width -30,44)];
   // [self.navigationHeader addSubview:spinner]; // spinner is not visible until started
    
    [spinner startAnimating];
}



- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
   // [self.navigationHeader addSubview:_progressView];
    
    [self initiateWebView];
}


- (void)viewDidLoad {
    [super viewDidLoad];
    
}


-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:YES];
    // [FIRAnalytics logEventWithName:@"view_anouncement" parameters:nil];
}



-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
   // [_progressView removeFromSuperview];
}




- (void)navigationBarBackPressed {
    [self.navigationController popViewControllerAnimated:YES];
}



//-(void)webViewProgress:(NJKWebViewProgress *)webViewProgress updateProgress:(float)progress
//{
//    [_progressView setProgress:progress animated:YES];
//    [spinner startAnimating];
//}




-(void)initiateWebView
{
    webView =[[UIWebView alloc]initWithFrame:CGRectMake(0, 50, self.view.bounds.size.width, self.view.bounds.size.height-50)];
    webView.scalesPageToFit = YES;
    NSURL *url = _url;
    NSURLRequest *requestObj = [NSURLRequest requestWithURL:url];
    webView.delegate = self;
    [ webView loadRequest:requestObj];
    [self.view addSubview:webView];
    //[_progressView setProgress:.4 animated:YES];
    [spinner startAnimating];
}



- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    NSLog(@"didFailLoadWithError %@",error);
    
    [spinner stopAnimating];
   // [_progressView setProgress:1 animated:YES];
}



- (void)webViewDidStartLoad:(UIWebView *)aWebView
{
   // [_progressView setProgress:.5 animated:YES];
    [spinner startAnimating];
}



- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    [spinner stopAnimating];
   // [_progressView setProgress:1 animated:YES];
}



- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}



- (UIStatusBarStyle)preferredStatusBarStyle {
    return UIStatusBarStyleLightContent;
}



@end
