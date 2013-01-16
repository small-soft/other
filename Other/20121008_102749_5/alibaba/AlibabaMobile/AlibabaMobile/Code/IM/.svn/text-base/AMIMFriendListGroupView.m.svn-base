//
//  AMIMFriendListGroupView.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-12.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIMFriendListGroupView.h"
#import "UIHelp.h"
#import "StringUtils.h"
#import "AliImageControlFactory.h"

@interface AMIMFriendListGroupView()

@end

@implementation AMIMFriendListGroupView

@synthesize arrowImageView = _arrowImageView;
@synthesize titleLabel = _titleLabel;
@synthesize numLabel = _numLabel;
@synthesize groupBtn = _groupBtn;

- (void) dealloc
{
    [_arrowImageView release];
    [_titleLabel release];
    [_numLabel release];
    [_groupBtn release];
    
    [super dealloc];
}

- (id)init
{
    self = [super initWithFrame:CGRectMake(0, 0, 320, 44) ];
    if (self) {
        [self initContentView];
    }
    return self;
}

- (void) initContentView
{
    
//    self.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"bg_aliww_grouplist"]];
    self.backgroundColor = [UIHelp colorWithHexString:@"F0F0F0"];
    
    
    _arrowImageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"icon_aliww_list01"]];
    [_arrowImageView sizeToFit];
//    _arrowImageView.frame = CGRectMake(15, (self.frame.size.height - _arrowImageView.frame.size.height)/2, _arrowImageView.frame.size.width, _arrowImageView.frame.size.height);
    _arrowImageView.frame = CGRectMake(10, (self.frame.size.height - _arrowImageView.frame.size.height)/2, _arrowImageView.frame.size.width, _arrowImageView.frame.size.height);
    [self addSubview:_arrowImageView];
    
    _titleLabel = [[UILabel alloc] init ];
    _titleLabel.backgroundColor = [UIColor clearColor];
    _titleLabel.font = [UIFont boldSystemFontOfSize:16.0f];
    _titleLabel.textColor = [UIColor blackColor];
    _titleLabel.text = @" ";
    [_titleLabel sizeToFit];
    _titleLabel.frame = CGRectMake(_arrowImageView.frame.origin.x + _arrowImageView.frame.size.width + 5, (self.frame.size.height - _titleLabel.frame.size.height)/2, _titleLabel.frame.size.width, _titleLabel.frame.size.height);
    [self addSubview: _titleLabel];
    
    _numLabel = [[UILabel alloc] init ];
    _numLabel.backgroundColor = [UIColor clearColor];
    _numLabel.font = [UIFont systemFontOfSize:14.0f];
    _numLabel.textColor = [UIHelp colorWithHexString:@"0x999999"]; 
    _numLabel.text = @" ";
    [_numLabel sizeToFit];
    _numLabel.frame = CGRectMake(_titleLabel.frame.origin.x + _titleLabel.frame.size.width + 10, _titleLabel.frame.origin.y+_titleLabel.frame.size.height-_numLabel.frame.size.height, _numLabel.frame.size.width, _numLabel.frame.size.height);
    [self addSubview: _numLabel];
    
    _groupBtn = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, self.frame.size.width, self.frame.size.height)];
    _groupBtn.backgroundColor = [UIColor clearColor];
    [self addSubview:_groupBtn];
    
    UIImageView * lineDivided = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"line_gray"]];
    lineDivided.frame = CGRectMake(0, 43, 320, 1);
    [self addSubview:lineDivided];
    [lineDivided release];
}

- (void) setTitle:(NSString *)title num:(NSString *)num
{
    _titleLabel.text = title;
    _numLabel.text = num;
    
    [_titleLabel sizeToFit];
    [_numLabel sizeToFit];
    
    _numLabel.frame = CGRectMake(_titleLabel.frame.origin.x + _titleLabel.frame.size.width+10, _titleLabel.frame.origin.y+_titleLabel.frame.size.height-_numLabel.frame.size.height, _numLabel.frame.size.width, _numLabel.frame.size.height);
}

@end
