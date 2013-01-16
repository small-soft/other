//
//  MessageListCell.m
//  AlibabaMobile
//
//  Created by  on 12-2-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MessageListCell.h"
#import "UIHelp.h"

#define  SUB_MAX_HEIGHT 1000
#define  SUB_MAX_WIDTH 274

@interface MessageListCell()

@end

@implementation MessageListCell

@synthesize mSubjectLabel   = _mSubjectLabel;
@synthesize mDateLabel      = _mDateLabel;
@synthesize mTypeLabel      = _mTypeLabel;
@synthesize mNewMessageIcon = _mNewMessageIcon;

- (void) setSubject:(NSString *)subject {
    self.mSubjectLabel.text = subject;
    
    [_mSubjectLabel setNumberOfLines:0];
    _mSubjectLabel.lineBreakMode = UILineBreakModeCharacterWrap;
    
    int subjectLabelHeight = [subject sizeWithFont:[UIFont boldSystemFontOfSize:16.0f] constrainedToSize:CGSizeMake(SUB_MAX_WIDTH, SUB_MAX_HEIGHT) lineBreakMode:UILineBreakModeCharacterWrap].height;
    
    self.mSubjectLabel.frame = CGRectMake(self.mSubjectLabel.frame.origin.x, self.mSubjectLabel.frame.origin.y, self.mSubjectLabel.frame.size.width, subjectLabelHeight);
    
    self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, (10 + subjectLabelHeight + 10 + 21 + 10));
    self.mDateLabel.frame = CGRectMake(self.mDateLabel.frame.origin.x, self.mSubjectLabel.frame.origin.y + self.mSubjectLabel.frame.size.height + 20, self.mDateLabel.frame.size.width, self.mDateLabel.frame.size.height);
    
    self.mTypeLabel.frame = CGRectMake(self.mTypeLabel.frame.origin.x, self.mSubjectLabel.frame.origin.y + self.mSubjectLabel.frame.size.height + 20, self.mDateLabel.frame.size.width, self.mDateLabel.frame.size.height);
}

+ (int) getCellHeightWithSubject:(NSString *)subject {
    int subjectLabelHeight = [subject sizeWithFont:[UIFont boldSystemFontOfSize:16.0f] constrainedToSize:CGSizeMake(SUB_MAX_WIDTH, SUB_MAX_HEIGHT) lineBreakMode:UILineBreakModeCharacterWrap].height;
    
    return (10 + subjectLabelHeight + 10 + 21 + 10);
}

-(void)dealloc {
    [_mSubjectLabel release];
    [_mDateLabel release];
    [_mTypeLabel release];
    
    [super dealloc];
}

@end
