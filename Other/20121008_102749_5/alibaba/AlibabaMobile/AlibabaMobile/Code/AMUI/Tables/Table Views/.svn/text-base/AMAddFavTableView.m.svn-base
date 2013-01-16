//
//  AMAddFavTableView.m
//  AlibabaMobile
//
//  Created by  on 12-7-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMAddFavTableView.h"
#import "AMIMViewController.h"
#import "LoginToken.h"
#import "AMFavoriteRequest.h"
#import "ConstDef.h"
#import "AMCUDResult.h"
#import <objc/runtime.h>
#import "AliToastView.h"
#import "AMPriceBaseItem.h"
#import "AMFavoriteBaseItem.h"

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]

@implementation AMAddFavTableView

@synthesize favDelegate = _favDelegate;

-(void)dealloc
{
    AM_RELEASE_SAFELY(_swipeGesture);
    AM_RELEASE_SAFELY(_favDelegate);
    AM_RELEASE_SAFELY(_swipedIndexPath);
    [super dealloc];
}

-(void)setSwipGesture
{
    if (!_swipeGesture) {
        _swipeGesture = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(didSwipe:)];
        [_swipeGesture setDirection:(UISwipeGestureRecognizerDirectionRight | UISwipeGestureRecognizerDirectionLeft)];
        [self addGestureRecognizer:_swipeGesture];
    }
}


-(UINavigationController*)navigationController
{
    Ivar ivar = class_getInstanceVariable([UIView class], "_viewDelegate");
    UIViewController *controller = object_getIvar(self, ivar);
    if (!controller) {
        controller = object_getIvar(self.superview, ivar);
    }
    return controller.navigationController;
}

-(void)showFavAlertView
{
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    if([loginUserName length] <= 3){  
        
        UIViewController *nextController;
        nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
        nextController.hidesBottomBarWhenPushed=YES;
        
        [[self navigationController] pushViewController:nextController animated:YES];
    }else{
        NSString *msg = [NSString stringWithFormat:@"加入收藏夹？"];
        UIAlertView *alert = [[UIAlertView alloc] 
                              initWithTitle:@"" 
                              message:msg 
                              delegate:self    
                              cancelButtonTitle:@"取消"                          otherButtonTitles:@"确定" ,
                              nil] ; 
        [alert show]; 
        [msg release];
        [alert release];
    }
    
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0) {  
        AM_RELEASE_SAFELY(_swipedIndexPath);
        NSLog(@"取消收藏");
    }
    else {    
        NSLog(@"收藏");        
        if ([self.favDelegate respondsToSelector:@selector(AMAddFavTableView:addPriceToFav:)]&&[self.favDelegate respondsToSelector:@selector(addPriceToFav:)]) {
            AMPriceItem*data = [self.favDelegate AMAddFavTableView:self addPriceToFav:_swipedIndexPath];
            if (data) {
                [self.favDelegate addPriceToFav:data];
                AM_RELEASE_SAFELY(_swipedIndexPath);
                return;
            }
        }
        
        if ([self.favDelegate respondsToSelector:@selector(AMAddFavTableView:addOfferToFav:)]&&[self.favDelegate respondsToSelector:@selector(addOfferToFav:)]) {
            AMOffer*data = [self.favDelegate AMAddFavTableView:self addOfferToFav:_swipedIndexPath];
            if (data) {
                [self.favDelegate addOfferToFav:data];
                AM_RELEASE_SAFELY(_swipedIndexPath);
                return;
            }
        }
        
        if ([self.favDelegate respondsToSelector:@selector(AMAddFavTableView:addCompanyToFav:)]&&[self.favDelegate respondsToSelector:@selector(addCompanyToFav:)]) {
            AMCompany*data = [self.favDelegate AMAddFavTableView:self addCompanyToFav:_swipedIndexPath];
            if (data) {
                [self.favDelegate addCompanyToFav:data];
                AM_RELEASE_SAFELY(_swipedIndexPath);
                return;
            }
        }
    }
}

- (void)didSwipe:(UISwipeGestureRecognizer *)gestureRecognizer {
    if (self.favDelegate) {
        if (gestureRecognizer.state == UIGestureRecognizerStateEnded) {
            
            CGPoint swipeLocation = [gestureRecognizer locationInView:self];
            _swipedIndexPath = [self indexPathForRowAtPoint:swipeLocation];
            if ([self.favDelegate respondsToSelector:@selector(AMAddFavTableView:addPriceToFav:)]) {
                AMPriceItem * data = [self.favDelegate AMAddFavTableView:self addPriceToFav:_swipedIndexPath];
                if (data) {
                    [self showFavAlertView];
                    return;
                }
            }
            if ([self.favDelegate respondsToSelector:@selector(AMAddFavTableView:addOfferToFav:)]) {
                AMOffer*data = [self.favDelegate AMAddFavTableView:self addOfferToFav:_swipedIndexPath];
                if (data) {
                    [self showFavAlertView];
                    return;
                }
            }
            if ([self.favDelegate respondsToSelector:@selector(AMAddFavTableView:addCompanyToFav:)]) {
                AMCompany*data = [self.favDelegate AMAddFavTableView:self addCompanyToFav:_swipedIndexPath];
                if (data) {
                    [self showFavAlertView];
                    return;
                }
            }
        }
        
    }
}
-(void)setupView
{
    self.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
    self.separatorColor = RGB(0xe0,0xe0,0xe0);
    self.backgroundColor = RGB(0xF0,0xf0,0xf0);
    
}

-(void)awakeFromNib
{
    [super awakeFromNib];
    [self setupView];
    [self setSwipGesture];
}


@end

