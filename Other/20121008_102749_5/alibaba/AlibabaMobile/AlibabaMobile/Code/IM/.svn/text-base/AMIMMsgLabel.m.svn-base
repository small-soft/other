//
//  AMIMMsgLabel.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-3-30.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIMMsgLabel.h"
#import "UIHelp.h"
#import "InternetDataTool.h"



#define  LABEL_MAX_WIDTH 200
#define  LABEL_MAX_HEIGHT 1000
#define  LABEL_FONT_SIZE 16.0f
#define  LABEL_TEXT_COLOR 0x000000
#define  LABEL_LINE_HEIGHT 24
#define  LABEL_IMAGE_WIDTH 24
#define  LABEL_LINE_SEPECTOR = 3



@interface AMIMMsgLabel()
{
    int nowX;
    int nowY;
    int maxWidth;
}

@end

@implementation AMIMMsgLabel


- (void)dealloc
{
    
    [super dealloc];
}

- (id)init
{
    self = [super init];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
            }
    return self;
}

- (NSString *) returnRevMessageString:(NSString *)_string {
	NSArray *rAry = [NSArray arrayWithArray:[InternetDataTool create].facesCharArray];
	NSString *replaceStr;
	NSString *returnStr = _string;
	
    returnStr = [returnStr stringByReplacingOccurrencesOfString:@"\r" withString:@""];
	for (int i = 0; i < [rAry count]; i++) {
		
		TextViewExItem *dicItem = [rAry objectAtIndex:i];
		NSString *imageStr = dicItem.imagePath;
		
		replaceStr = dicItem.iconPath;
		returnStr = [returnStr stringByReplacingOccurrencesOfString:imageStr withString:replaceStr];
		
	}
	
	return returnStr;
}

//by tom.lih 逻辑可以尝试进一步简化
- (CGSize) setContentStr:(NSString *)contentStr
{
    maxWidth = 0;
    nowX = 0;
    nowY = 0;
    
    contentStr = [self returnRevMessageString:contentStr];  
    
    while(contentStr.length > 0){
        
        NSRange faceRange = [contentStr rangeOfString:@"\\T"];
        NSRange tempRange;
        NSString * strTemp;
        BOOL bTemp1=FALSE;
        BOOL bTemp2=FALSE;
        if(faceRange.location == NSNotFound){
            [self generateTextLinesWithOutFace:contentStr];
            contentStr =[contentStr substringFromIndex:[contentStr length]];
            break;
        }else {
            
            if ([contentStr isEqualToString:@"\\T"] ) {
                [self generateTextLinesWithOutFace:contentStr];
                contentStr =[contentStr substringFromIndex:[contentStr length]];
                break;
            }
            
            if ( faceRange.location > 0) {
                
                tempRange.location=0;
                tempRange.length=faceRange.location;
                [self generateTextLinesWithOutFace:[contentStr substringWithRange : tempRange]];
                
            }
            
            if ( faceRange.location+9 <= [contentStr length]) {
                
                strTemp=[contentStr substringWithRange:NSMakeRange(faceRange.location+5,4)];
                
                if ( [strTemp isEqualToString:@".png"] ) {
                    strTemp=[contentStr substringWithRange:NSMakeRange(faceRange.location+2,7)];
                    [self generateFaceView:strTemp];
                    bTemp1=TRUE;
                }else {
                    bTemp2=TRUE;
                }
                
            }else {
                [self generateTextLinesWithOutFace:contentStr];
                contentStr =[contentStr substringFromIndex:[contentStr length]];
                break;
            }
            
            
            if (bTemp1) {                    
                
                contentStr =[contentStr substringFromIndex:faceRange.location+9];
                
                tempRange.location=0;
                tempRange.length=2;
                
                if (([contentStr length] >= 2) &&[[contentStr substringWithRange:tempRange] isEqualToString:@"\\T"] ) {
                    tempRange.location=5;
                    tempRange.length=4;
                    if (([contentStr length] >= 9) && ([[contentStr substringWithRange:tempRange] isEqualToString:@".png" ])) {
                        
                    }else {
                        
                        contentStr =[contentStr substringFromIndex:2];
                        
                    }         
                }
                
            }else {
                if (bTemp2) {
                    [self generateTextLinesWithOutFace:@"\\T"];
                    contentStr =[contentStr substringFromIndex:2];
                }else {
                    contentStr =[contentStr substringFromIndex:faceRange.location];
                }
                
            }
            
        }
    }
    
    self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, maxWidth, nowY + LABEL_LINE_HEIGHT);
    return self.frame.size;
}


- (void) generateTextLines:(NSString *)text
{
    while (text.length >0) {
        int width = LABEL_MAX_WIDTH - nowX;
        if(width <LABEL_IMAGE_WIDTH){
            nowX = 0;
            nowY += LABEL_LINE_HEIGHT;
            maxWidth = LABEL_MAX_WIDTH;
            width = LABEL_MAX_WIDTH;
        }
        int index = [self getSubstring:text withWidth:width];
        if(index >0){
            NSString * nowStr = [text substringToIndex:index];
            [self generatetextLabel:nowStr];
            
        }
        if(index < text.length){
            text = [text substringFromIndex:index];
        }else{
            text = @"";
        }
    }
}

- (void) generateTextLinesWithOutFace:(NSString *)text
{
    if (text.length <= 0) {
        return;
    }

    int width = LABEL_MAX_WIDTH - nowX;
    if(width <LABEL_IMAGE_WIDTH){
        nowX = 0;
        nowY += LABEL_LINE_HEIGHT;
        maxWidth = LABEL_MAX_WIDTH;
        width = LABEL_MAX_WIDTH;
    }
    
    if(nowX > 0){
        int index = [self getSubstring:text withWidth:width];
        if(index >0){
            NSString * nowStr = [text substringToIndex:index];
            [self generatetextLabel:nowStr];
        }
        
        if(index < text.length){
            text = [text substringFromIndex:index];
        }else{
            text = @"";
        }
        
        if (text.length <= 0) {
            return;
        }
        
        nowX = 0;
        nowY += LABEL_LINE_HEIGHT;
        maxWidth = LABEL_MAX_WIDTH;
    }
     
    UILabel *label = [[UILabel alloc] init];
    label.backgroundColor = [UIColor clearColor];
    label.text = text;
    label.font = [UIFont systemFontOfSize:LABEL_FONT_SIZE];
    label.textColor = [UIColor blackColor];
    label.lineBreakMode = UILineBreakModeCharacterWrap;
    [label setNumberOfLines:0];
    
    CGSize labelSize = [text sizeWithFont:label.font constrainedToSize:CGSizeMake(LABEL_MAX_WIDTH, LABEL_MAX_HEIGHT) lineBreakMode:UILineBreakModeCharacterWrap];
    CGFloat height = labelSize.height;
    CGFloat labelWidth = labelSize.width;
    
    label.frame = CGRectMake(nowX, nowY, labelWidth, height);
    [self addSubview:label];
    nowX += label.frame.size.width;
    nowY += label.frame.size.height - LABEL_LINE_HEIGHT;
    maxWidth = (maxWidth > nowX ? maxWidth : nowX);
    [label release];
}

- (void) generatetextLabel:(NSString *)text
{
    UILabel *label = [[UILabel alloc] init];
    label.backgroundColor = [UIColor clearColor];
    label.text = text;
    label.font = [UIFont systemFontOfSize:LABEL_FONT_SIZE];
    label.textColor = [UIColor blackColor];
    int labelWidth = [UIHelp getLabelSizeWithFont:label.font labelString:text labelHeight:LABEL_LINE_HEIGHT].width;
    if(nowX + labelWidth > LABEL_MAX_WIDTH){
        nowX = 0;
        nowY += LABEL_LINE_HEIGHT;
        maxWidth = LABEL_MAX_WIDTH;
    }
    label.frame = CGRectMake(nowX, nowY, labelWidth, LABEL_LINE_HEIGHT);
    [self addSubview:label];
    nowX += label.frame.size.width;
    maxWidth = (maxWidth > nowX?maxWidth:nowX);
    [label release];
}

- (int) getSubstringOfString:(NSString *)srcStr withWidth:(int)width
{
    UIFont * font = [UIFont systemFontOfSize:LABEL_FONT_SIZE];
    NSString  * string = [NSString stringWithString:srcStr];
    
    while([string sizeWithFont:font].width > width && string.length > 0){
        string = [string substringToIndex:(string.length -1)];
    }

    return string.length;
}
 
- (int) getSubstring:(NSString *)srcStr withWidth:(int)width
{
    UIFont * font = [UIFont systemFontOfSize:LABEL_FONT_SIZE];
    NSString  * subStr;
    int idx = 0;
    for (; idx < srcStr.length; idx++) {
        subStr = [srcStr substringToIndex:idx];
        if ([subStr sizeWithFont:font].width > width) {
            if(idx > 0){
                idx--;
            }
            break;
        }
    }

    return idx;
}

- (void)generateFaceView:(NSString *)face
{
    UIImageView * faceView = [[UIImageView alloc] init];
    faceView.backgroundColor = [UIColor clearColor];
    faceView.image = [UIImage imageNamed:face];
    
    if(nowX + LABEL_IMAGE_WIDTH > LABEL_MAX_WIDTH){
        nowX = 0;
        nowY += LABEL_LINE_HEIGHT;
        maxWidth = LABEL_MAX_WIDTH;
    }
    faceView.frame = CGRectMake(nowX, nowY, LABEL_IMAGE_WIDTH, LABEL_IMAGE_WIDTH);
    [self addSubview:faceView];
    nowX += faceView.frame.size.width;
    maxWidth = (maxWidth > nowX?maxWidth:nowX);
    [faceView release];
}


@end
