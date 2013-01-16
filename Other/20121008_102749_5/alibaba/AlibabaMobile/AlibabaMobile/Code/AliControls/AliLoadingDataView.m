//
//  AliLoadingDataView.m
//  AlibabaMobile
//
//  Created by zzh on 12-2-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliLoadingDataView.h"

@interface AliLoadingDataView ()
@property (nonatomic, retain) NSMutableArray * lastRequestArray;
@end

@implementation AliLoadingDataView
@synthesize noDataView=_noDataView;
@synthesize loadingView = _loadingView;
@synthesize noDataMessageLabel = _noDataMessageLabel;
@synthesize loadFailedView = _loadFailedView;
@synthesize reloadButton = _reloadButton;
//@synthesize delegate = _delegate;
@synthesize lastRequestArray = _lastRequestArray;

-(NSArray *)lastRequestArray{
    if (nil ==_lastRequestArray) {
        _lastRequestArray = [[NSMutableArray alloc]init];
    }
    return _lastRequestArray;
}

- (void)dealloc{
    [_lastRequestArray release];
    [_noDataView release];
    [_loadingView release];
    [_noDataMessageLabel release];
    [_loadFailedView release];
    [_reloadButton release];
    [super dealloc];
}

-(void)awakeFromNib{
    UIImage *backgroundImageNor = [UIImage imageNamed:@"btn_ct_nor.png"];
    [self.reloadButton setBackgroundImage:[backgroundImageNor stretchableImageWithLeftCapWidth:backgroundImageNor.size.width/2 topCapHeight:backgroundImageNor.size.height/2] forState:UIControlStateNormal];
    UIImage *backgroundImagePress = [UIImage imageNamed:@"btn_ct_p.png"];
    [self.reloadButton setBackgroundImage:[backgroundImagePress stretchableImageWithLeftCapWidth:backgroundImagePress.size.width/2 topCapHeight:backgroundImagePress.size.height/2] forState:UIControlStateSelected];
    [self.reloadButton addTarget:self action:@selector(clickReloadButton:) forControlEvents:UIControlEventTouchUpInside];
}
//-(id)init{
//    if (self = [super init]) {
//        UIImage *backgroundImageNor = [UIImage imageNamed:@"btn_ct_nor.png"];
//        [self.reloadButton setBackgroundImage:[backgroundImageNor stretchableImageWithLeftCapWidth:backgroundImageNor.size.width/2 topCapHeight:backgroundImageNor.size.height/2] forState:UIControlStateNormal];
//        UIImage *backgroundImagePress = [UIImage imageNamed:@"btn_ct_p.png"];
//        [self.reloadButton setBackgroundImage:[backgroundImagePress stretchableImageWithLeftCapWidth:backgroundImagePress.size.width/2 topCapHeight:backgroundImagePress.size.height/2] forState:UIControlStateSelected];
//    }
//    return self;
//}
//
//-(id)initWithCoder:(NSCoder *)aDecoder{
//    if (self = [super initWithCoder:aDecoder]) {
//        UIImage *backgroundImageNor = [UIImage imageNamed:@"btn_ct_nor.png"];
//        [self.reloadButton setBackgroundImage:[backgroundImageNor stretchableImageWithLeftCapWidth:backgroundImageNor.size.width/2 topCapHeight:backgroundImageNor.size.height/2] forState:UIControlStateNormal];
//        UIImage *backgroundImagePress = [UIImage imageNamed:@"btn_ct_p.png"];
//        [self.reloadButton setBackgroundImage:[backgroundImagePress stretchableImageWithLeftCapWidth:backgroundImagePress.size.width/2 topCapHeight:backgroundImagePress.size.height/2] forState:UIControlStateSelected];
//    }
//    return self;
//}
-(void)showLoadingView
{
    self.hidden = NO;
    _loadingView.hidden = NO;
    _noDataView.hidden = YES;
    _loadFailedView.hidden = YES;
}

-(void)endLoadingView
{
    self.hidden = YES;
}

-(void)showNodataMessage
{
    self.hidden = NO;
    _loadingView.hidden = YES;
    _noDataView.hidden = NO;
    _loadFailedView.hidden = YES;
}

-(void)showLoadFailedMessageForRequest:(RKRequest*)request
{
//    @synchronized(self){
        if (![self.lastRequestArray count]) {
            NSMutableDictionary * dictionary = [[NSMutableDictionary alloc] init];
            [dictionary setObject:request forKey:@"request"];
            [dictionary setObject:@"NO" forKey:@"isSended"];
            [self.lastRequestArray addObject:dictionary];
            [dictionary release];
        }else {
            BOOL isInDic = NO;
            for (NSMutableDictionary * olddictionary in self.lastRequestArray) {
                if ([(RKRequest*)[olddictionary objectForKey:@"request"] isEqual: request]) {
                    [olddictionary setObject:@"NO" forKey:@"isSended"];
                    isInDic = YES;
                    break;
                }
                
            }
            if (!isInDic) {
                NSMutableDictionary * dictionary = [[NSMutableDictionary alloc] init];
                [dictionary setObject:request forKey:@"request"];
                [dictionary setObject:@"NO" forKey:@"isSended"];
                [self.lastRequestArray addObject:dictionary];
                [dictionary release];
            } 
        }
//    }
    self.hidden = NO;
    _loadFailedView.hidden = NO;
    _noDataView.hidden = YES;
    _loadingView.hidden = YES;
}
-(IBAction)clickReloadButton:(id)sender{
//    if (self.delegate) {
//        [self.delegate reloadLoadingData];
//    }
//    @synchronized(self){
        for (NSMutableDictionary * dictionary in self.lastRequestArray) {
            if ([(NSString*)[dictionary objectForKey:@"isSended"] isEqualToString:@"NO"]) {
                [(RKRequest*)[dictionary objectForKey:@"request"] send];
                [dictionary setObject:@"YES" forKey:@"isSended"];
                [self showLoadingView];
            }
//        }
    }
}
-(void)clearFailedRequest{
    self.lastRequestArray = nil;
}
@end
