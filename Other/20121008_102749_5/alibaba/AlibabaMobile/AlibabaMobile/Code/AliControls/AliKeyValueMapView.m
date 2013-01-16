//
//  AliKeyValueMapView.m
//  AlibabaMobile
//
//  Created by  on 12-2-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliKeyValueMapView.h"
#import "StringUtils.h"
#import "UIHelp.h"
#import "AliImageControlFactory.h"

static const int DEFAULT_PADDING = 15;
static const int DEFAULT_HORIZONTAL_SPACE = 5;
static const int DEFAULT_VERTICAL_SPACE = 10;
static NSString * DEFAULT_KEY_TEXT_COLOR = @"0x666666";
static NSString * DEFAULT_VALUE_TEXT_COLOR = @"0x000000";
static const float DEFAULT_FONT_SIZE = 14.0f;
static const int DEFAULT_KEY_ZONE_WIDTH = 80;
static const int DEFAULT_VALUE_ZONE_WIDTH = 200;
static const int DEFAULT_WIDTH = 320;
static const int  DEFAULT_TITLE_PADDING_LEFT = 10;



//value style
const int VALUE_STYLE_PLAIN = 0;

const int VALUE_STYLE_MULTI_HORIZONTAL = 1;


//item style
const int ITEM_STYLE_LINE_DIVIDED = 21;

const int ITEM_STYLE_ONE_LABEL = 22;

const int ITEM_STYLE_TITLE = 23;

const int ITEM_STYLE_CUSTOME= 24;

@interface AliKeyValueMapView()
{
}




@end


@implementation AliKeyValueMapView


@synthesize paddingTop = _paddingTop;
@synthesize paddingBottom = _paddingBottom;
@synthesize paddingLeft = _paddingLeft;
@synthesize paddingRight = _paddingRight;
@synthesize horizontalSpace = _horizontalSpace;
@synthesize verticalSpace = _verticalSpace;
@synthesize keyTextColor = _keyTextColor;
@synthesize valueTextColor = _valueTextColor;
@synthesize fontSize = _fontSize;
@synthesize keyZoneWidth = _keyZoneWidth;
@synthesize valueZoneWidth = _valueZoneWidth;
@synthesize alignCenter = _alignCenter;

- (id) init
{
    [super init ];
    if(self){
        
        _paddingTop = DEFAULT_PADDING;
        _paddingBottom = DEFAULT_PADDING;
        _paddingLeft = DEFAULT_PADDING;
        _paddingRight = DEFAULT_PADDING;
        
        _horizontalSpace = DEFAULT_HORIZONTAL_SPACE;
        _verticalSpace = DEFAULT_VERTICAL_SPACE;
        _keyTextColor = DEFAULT_KEY_TEXT_COLOR;
        _valueTextColor = DEFAULT_VALUE_TEXT_COLOR;
        _fontSize = DEFAULT_FONT_SIZE;
        _keyZoneWidth = DEFAULT_KEY_ZONE_WIDTH;
        _valueZoneWidth = DEFAULT_VALUE_ZONE_WIDTH;
        _alignCenter = YES;
        
        
        [super setBackgroundColor:[UIColor clearColor]];
    }
    return self;
}

-(void) setPadding:(int)padding
{
    _paddingTop = padding;
    _paddingBottom = padding;
    _paddingLeft = padding;
    _paddingRight = padding;
}

- (id) initWithKeyValues:(NSMutableArray *)array maxKeyLabelString:(const NSString*) maxKeyLabelString
{
    self = [self init];
    if(self){
        [self setContentArray:array maxKeyLabelString:maxKeyLabelString];
    }
    return self;
}

- (void) setContentArray:(NSMutableArray *)array  maxKeyLabelString:(const NSString*) maxKeyLabelString

{
    NSMutableArray * contentArray = [array retain];
    
    self.keyZoneWidth =  [StringUtils getStringSize:maxKeyLabelString font:[UIFont systemFontOfSize:self.fontSize]].width;
    self.valueZoneWidth = 320 - self.keyZoneWidth - self.paddingLeft - self.paddingRight - self.horizontalSpace - [StringUtils getStringSize:@"：" font:[UIFont systemFontOfSize:self.fontSize]].width;
    
    if(contentArray != nil && contentArray.count > 0){
        
        
        int keyLabelX = self.paddingLeft;
        int keyLabelWidth = self.keyZoneWidth;
        
        int dottedLabelX = keyLabelX + keyLabelWidth;
        int dottedLabelWidth = [StringUtils getStringSize:@"：" font:[UIFont systemFontOfSize:self.fontSize]].width;
        
        int valueLabelX = dottedLabelX + dottedLabelWidth +self.horizontalSpace;
        int valueLabelWidth = self.valueZoneWidth;
        
        int tempY = self.paddingTop;
        
        NSLog(@"the padding top is : %d" , tempY);
        
        int lineHeight = 21;

        int size = contentArray.count;
        for(int i=0; i<size; i++){
            
            KeyValueObject * obj = [contentArray objectAtIndex:i];
            
            
            int objType = obj.type;
            
            
            if(objType == ITEM_STYLE_ONE_LABEL ){
                UILabel * label = [[UILabel alloc] init];
                label.font = [UIFont systemFontOfSize:self.fontSize];
                label.textColor = [UIHelp colorWithHexString:self.keyTextColor];
                label.backgroundColor = [UIColor clearColor];
                label.textAlignment = UITextAlignmentLeft;
                label.numberOfLines = 0;
                label.lineBreakMode = UILineBreakModeWordWrap;
                
                label.text = [NSString stringWithFormat:@"%@  %@", obj.key, obj.value];
                
                int labelWidth = DEFAULT_WIDTH - self.paddingLeft - self.paddingRight;
                int labelHeight = [UIHelp getLabelSizeWithFont:label.font labelString:label.text labelWidth:labelWidth].height;
                label.frame = CGRectMake(keyLabelX, tempY, labelWidth, labelHeight);
                
                [self addSubview:label];
                lineHeight = labelHeight;
                
                [label release];
            }else if(objType == ITEM_STYLE_LINE_DIVIDED){
                AliImageButton * dividedIcon = [[[AliImageControlFactory sharedInstance] getImageButtonWithType:LINE_DIVIDED] retain];
                dividedIcon.frame = CGRectMake(0, tempY, dividedIcon.frame.size.width, dividedIcon.frame.size.height);
                [self addSubview:dividedIcon];
                lineHeight = dividedIcon.frame.size.height;
                
                [dividedIcon release];
            }else if(objType == ITEM_STYLE_TITLE){
                AliImageButton * bkImg = [[AliImageControlFactory sharedInstance] getImageButtonWithType:SUB_TITLE_BACKGROUND];
                bkImg.frame = CGRectMake(0, tempY, bkImg.frame.size.width, bkImg.frame.size.height);
                [self addSubview:bkImg];
                
                UILabel * label = [[UILabel alloc] init];
                label.font = [UIFont systemFontOfSize:self.fontSize];
                label.textColor = [UIHelp colorWithHexString:self.valueTextColor];
                label.backgroundColor = [UIColor clearColor];
                label.textAlignment = UITextAlignmentLeft;
                label.numberOfLines = 0;
                label.lineBreakMode = UILineBreakModeWordWrap;
                
                label.text = obj.value;
                
                int labelWidth = DEFAULT_WIDTH - self.paddingLeft - self.paddingRight;
                int labelHeight = [UIHelp getLabelSizeWithFont:label.font labelString:label.text labelWidth:DEFAULT_WIDTH].height;
                label.frame = CGRectMake(DEFAULT_TITLE_PADDING_LEFT, tempY + (bkImg.frame.size.height-labelHeight)/2, labelWidth, labelHeight);
                
                [self addSubview:label];
                lineHeight = bkImg.frame.size.height;
                
                [label release];

            }else if(objType == ITEM_STYLE_CUSTOME){
                UIView * view = [obj.value retain];
                
                view.frame = CGRectMake((320-view.frame.size.width)/2, tempY, view.frame.size.width, view.frame.size.height);
                [self addSubview:view];
                lineHeight = view.frame.size.height;
                [view release];
            }else{
                //add key label
                NSString * keyText = obj.key;
                UILabel * keyLabel = [[UILabel alloc] init];
                keyLabel.font = [UIFont systemFontOfSize:self.fontSize];
                keyLabel.textColor = [UIHelp colorWithHexString:self.keyTextColor];
                keyLabel.backgroundColor = [UIColor clearColor];
                if(!_alignCenter){
                    keyLabel.textAlignment = UITextAlignmentLeft;
                }else{
                    keyLabel.textAlignment = UITextAlignmentRight;
                }
                
                keyLabel.numberOfLines = 0;
                keyLabel.lineBreakMode = UILineBreakModeWordWrap;
                
                keyLabel.text = keyText;
                
                if(!_alignCenter){
                    keyLabelWidth = [StringUtils getStringSize:keyLabel.text font:[UIFont systemFontOfSize:self.fontSize]].width;
                    dottedLabelX = keyLabelX + keyLabelWidth;
                    valueLabelX = dottedLabelX + dottedLabelWidth +self.horizontalSpace;
                }
                int keyLabelHeight = [UIHelp getLabelSizeWithFont:keyLabel.font labelString:keyLabel.text labelWidth:keyLabelWidth].height;
                keyLabel.frame = CGRectMake(keyLabelX, tempY, keyLabelWidth, keyLabelHeight);
                
                [self addSubview:keyLabel];
                [keyLabel release];
                
                //add dotted label
                UILabel * dottedLabel = [[UILabel alloc] init];
                dottedLabel.font = [UIFont systemFontOfSize:self.fontSize];
                dottedLabel.textColor = [UIHelp colorWithHexString:self.keyTextColor];
                dottedLabel.backgroundColor = [UIColor clearColor];
                dottedLabel.numberOfLines = 1;
                dottedLabel.text = @"：";
                [dottedLabel sizeToFit];
                dottedLabel.frame = CGRectMake(dottedLabelX, tempY, dottedLabel.frame.size.width, dottedLabel.frame.size.height);
                [self addSubview:dottedLabel];
                [dottedLabel release];
                
                //add value views
                int  valueType = obj.type;
                if(valueType == VALUE_STYLE_PLAIN){
                    NSString * valueText = obj.value;
                    
                    UILabel * valueLabel = [[UILabel alloc] init];
                    
                    valueLabel.font = [UIFont systemFontOfSize:self.fontSize];
                    valueLabel.textColor = [UIHelp colorWithHexString:self.valueTextColor];
                    valueLabel.backgroundColor = [UIColor clearColor];
                    valueLabel.textAlignment = UITextAlignmentLeft;
                    valueLabel.numberOfLines = 0;
                    valueLabel.lineBreakMode = UILineBreakModeWordWrap;
                    
                    valueLabel.text = valueText;
                    
                    int valueLabelHeight = [UIHelp getLabelSizeWithFont:valueLabel.font labelString:valueLabel.text labelWidth:valueLabelWidth].height;
                    valueLabel.frame = CGRectMake(valueLabelX, tempY, valueLabelWidth, valueLabelHeight);
                    
                    [self addSubview:valueLabel];
                    [valueLabel release];
                    
                    lineHeight = (keyLabelHeight > valueLabelHeight? keyLabelHeight : valueLabelHeight);
                }else if(valueType == VALUE_STYLE_MULTI_HORIZONTAL){
                    NSMutableArray * viewArray = obj.value;
                    if(viewArray != nil && viewArray.count > 0){
                        int viewArraySize = viewArray.count;
                        int valueTempX = valueLabelX;
                        lineHeight = keyLabelHeight;
                        for(int j=0; j<viewArraySize; j++){
                            id viewObject = [viewArray objectAtIndex:j];
                            if([viewObject isKindOfClass:[NSString class]]){
                                NSString * valueText = viewObject;
                                
                                UILabel * valueLabel = [[UILabel alloc] init];
                                
                                valueLabel.font = [UIFont systemFontOfSize:self.fontSize];
                                valueLabel.textColor = [UIHelp colorWithHexString:self.valueTextColor];
                                valueLabel.backgroundColor = [UIColor clearColor];
                                valueLabel.textAlignment = UITextAlignmentLeft;
                                valueLabel.numberOfLines = 1;
                                
                                valueLabel.text = valueText;
                                [valueLabel sizeToFit];
                                
                                valueLabel.frame = CGRectMake(valueTempX, tempY, valueLabel.frame.size.width, valueLabel.frame.size.height);
                                
                                [self addSubview:valueLabel];
                                
                                valueTempX += valueLabel.frame.size.width + self.horizontalSpace;
                                lineHeight = (lineHeight>valueLabel.frame.size.height?lineHeight:valueLabel.frame.size.height);
                                [valueLabel release];
                                
                            }else if([viewObject isKindOfClass:[UIView class]]){
                                UIView * valueView = (UIView *)viewObject;
                                valueView.frame = CGRectMake(valueTempX, tempY, valueView.frame.size.width, valueView.frame.size.height);
                                [self addSubview:valueView];
                                valueTempX += valueView.frame.size.width + self.horizontalSpace;
                                lineHeight = (lineHeight>valueView.frame.size.height?lineHeight:valueView.frame.size.height);
                            }
                        }
                    }
                    
                }else{
                    
                } 
            }
               
            if(i < size-1)
                tempY += (lineHeight + self.verticalSpace);
            else
                tempY += lineHeight;
        }
        NSLog(@"the padding bottome is %d " , self.paddingBottom);
        tempY += self.paddingBottom;
        self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, tempY);
    }
    
    [contentArray release];
}

-(void) dealloc
{
    self.keyTextColor = nil;
    self.valueTextColor = nil;
    [super dealloc];
}

@end
