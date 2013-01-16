//
//  AliSearchResultView.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliSearchResultView.h"
@interface AliSearchResultView()
@property (nonatomic,retain)AliCustomLabel *title;
@property (nonatomic,retain)AliCustomLabel *preTitle;
@property (nonatomic,retain)AliCustomLabel *sufTitle;
@end

@implementation AliSearchResultView
@synthesize title=_title;
@synthesize preTitle=_preTitle;
@synthesize sufTitle=_sufTitle;
- (void)dealloc {
    [_title release];
    [_preTitle release];
    [_sufTitle release];
    [super dealloc];
}
-(AliCustomLabel*)preTitle
{
    if (!_preTitle) {
        _preTitle = [[AliCustomLabel alloc]init];
    }
    return _preTitle;
}
-(AliCustomLabel*)title
{
    if (!_title) {
        _title = [[AliCustomLabel alloc]init];
    }
    return _title;
}
-(AliCustomLabel*)sufTitle
{
    if (!_sufTitle) {
        _sufTitle = [[AliCustomLabel alloc]init];
    }
    return _sufTitle;
}
-(void)awakeFromNib
{
    [super awakeFromNib];
    self.backgroundColor = [UIColor clearColor];
    [self setupPreTitle];
    [self setupTitle];
    [self setupSufTitle];
   
}

-(void)setupPreTitle
{
    self.preTitle.fontSize = 12.0;
    self.preTitle.r = 0x66;
    self.preTitle.g = 0x66;
    self.preTitle.b = 0x66;
    self.preTitle.frame = CGRectMake(0.0, 0.0, 0.0, 0.0);
    [self.preTitle setupView];
    [self addSubview:self.preTitle];
    
}
-(void)setupTitle
{
    self.title.fontSize = 12.0;
    self.title.r = 0xff;
    self.title.g = 0x73;
    self.title.b = 0x00;
    self.title.frame = CGRectMake(0.0, 0.0, 0.0, 0.0);
    [self.title setupView];
    [self addSubview:self.title];
}
-(void)setupSufTitle
{
    self.sufTitle.fontSize = 12.0;
    self.sufTitle.r = 0x66;
    self.sufTitle.g = 0x66;
    self.sufTitle.b = 0x66;
    self.sufTitle.frame = CGRectMake(0.0, 0.0, 0.0, 0.0);
    [self.sufTitle setupView];
    [self addSubview:self.sufTitle];
}

-(void)setupData:(NSString*)title pre:(NSString*)preTitle suf:(NSString*)sufTitle
{
    {
    self.preTitle.text = preTitle;
    CGSize labelSize = [self.preTitle.text sizeWithFont:self.preTitle.font];
    self.preTitle.frame = CGRectMake(8.0, (self.frame.size.height - self.preTitle.fontSize)/2, labelSize.width, self.preTitle.fontSize);
    }
    {
        self.title.text = title;
        CGSize labelSize = [self.title.text sizeWithFont:self.title.font];
        self.title.frame = CGRectMake(self.preTitle.frame.origin.x+self.preTitle.frame.size.width, (self.frame.size.height - self.title.fontSize)/2, labelSize.width, self.title.fontSize);
    }
    {
        self.sufTitle.text = sufTitle;
        CGSize labelSize = [self.sufTitle.text sizeWithFont:self.sufTitle.font];
        self.sufTitle.frame = CGRectMake(self.title.frame.origin.x+self.title.frame.size.width, (self.frame.size.height - self.sufTitle.fontSize)/2, labelSize.width, self.sufTitle.fontSize);
    }
}
@end
