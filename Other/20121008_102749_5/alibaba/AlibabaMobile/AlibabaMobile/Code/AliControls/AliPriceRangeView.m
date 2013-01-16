//
//  AliPriceRangeView.m
//  AlibabaMobile
//
//  Created by  on 12-2-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliPriceRangeView.h"
#import "AMPrice.h"
#import "StringUtils.h"
#import "UIHelp.h"


static const float DEFAULT_PRICE_FONT_SIZE = 14.0f;
static const float DEFAULT_RANGE_FONT_SIZE = 12.0f;
static NSString * DEFAULT_PRICE_NUM_COLOR = @"0xCC0000";
static NSString * DEFAULT_RANGE_CHAR_COLOR = @"0x999999";
static const int DEFAULT_PADDING = 0;
static const int DEFAULT_HORIZONTAL_SPACE = 5;
static const int DEFAULT_VERTICAL_SPACE = 15;

@interface AliPriceRangeView()
{
}



@end

@implementation AliPriceRangeView

@synthesize paddingTop = _paddingTop;
@synthesize paddingBottom = _paddingBottom;
@synthesize paddingLeft = _paddingLeft;
@synthesize paddingRight = _paddingRight;
@synthesize horizontalSpace = _horizontalSpace;
@synthesize verticalSpace = _verticalSpace;
@synthesize priceFontSize = _priceFontSize;
@synthesize rangeFontSize = _rangeFontSize;
@synthesize priceNumColor = _priceNumColor;
@synthesize rangeCharColor = _rangeCharColor;

-(id)init
{
    [super init];
    if(self){
        
        _paddingTop = DEFAULT_PADDING;
        _paddingBottom = DEFAULT_PADDING;
        _paddingLeft = DEFAULT_PADDING;
        _paddingRight = DEFAULT_PADDING;
        
        _horizontalSpace = DEFAULT_HORIZONTAL_SPACE;
        _verticalSpace = DEFAULT_VERTICAL_SPACE;
        _priceNumColor = DEFAULT_PRICE_NUM_COLOR;
        _priceFontSize = DEFAULT_PRICE_FONT_SIZE;
        _rangeCharColor = DEFAULT_RANGE_CHAR_COLOR;
        _rangeFontSize = DEFAULT_RANGE_FONT_SIZE;
    }
    return self;
}

-(id) initWithPriceRanges:(NSArray *) priceRanges productUnit:(NSString *)unit
{
    self = [self init];
    if(self){
        [self setPriceRangeArray:priceRanges productUnit:unit];
    }
    return self;
}

-(void) setPriceRangeArray:(NSArray *)priceRangeArray productUnit:(NSString *)unit
{
    NSArray *contentArray = [priceRangeArray retain];
    NSString *productUnit = [unit retain];
    if(contentArray != nil && contentArray.count >0){
        int size = contentArray.count;
        
        int labelX = self.paddingLeft;
        
        int tempY = self.paddingTop;
        
        int width = 0;
        for(int i=0;i<size;i++){
            int tempWidth = 0;
            AMPrice * price = [contentArray objectAtIndex:i];

            UILabel * symbolLabel = [[UILabel alloc] init];
            symbolLabel.backgroundColor = [UIColor clearColor];
            symbolLabel.font = [UIFont systemFontOfSize:self.priceFontSize];
            symbolLabel.textColor = [UIHelp colorWithHexString:DEFAULT_PRICE_NUM_COLOR];
            symbolLabel.text = @" ¥ ";
            [symbolLabel sizeToFit];
            symbolLabel.frame = CGRectMake(labelX, tempY, symbolLabel.frame.size.width, symbolLabel.frame.size.height);
            [self addSubview:symbolLabel];
            labelX += symbolLabel.frame.size.width;
            [symbolLabel release];
            
            
            UILabel * priceLabel = [[UILabel alloc] init];
            priceLabel.backgroundColor = [UIColor clearColor];
            priceLabel.font = [UIFont boldSystemFontOfSize:self.priceFontSize];
            priceLabel.textColor = [UIHelp colorWithHexString:self.priceNumColor];
            priceLabel.text = [NSString stringWithFormat:@"%.2f", price.price.floatValue];

            [priceLabel sizeToFit];
            
            priceLabel.frame = CGRectMake(labelX, tempY, priceLabel.frame.size.width, priceLabel.frame.size.height);
            [self addSubview:priceLabel];
            labelX += (priceLabel.frame.size.width + 15);
            int tempLineHeight = priceLabel.frame.size.height;
            [priceLabel release];
            
            UILabel * rangeLabel = [[UILabel alloc] init];
            rangeLabel.backgroundColor = [UIColor clearColor];
            rangeLabel.font = [UIFont systemFontOfSize:DEFAULT_RANGE_FONT_SIZE];
            rangeLabel.textColor = [UIHelp colorWithHexString:DEFAULT_RANGE_CHAR_COLOR];
            if(price.endAmount.floatValue >0){
                rangeLabel.text=  [[NSString alloc] initWithFormat:@"(%@-%@%@)", price.beginAmount.stringValue, price.endAmount.stringValue, productUnit];
                    
            }else{
                rangeLabel.text=  [[NSString alloc] initWithFormat:@"(%@%@以上)",price.beginAmount.stringValue,  productUnit];
                        
            }
            [rangeLabel sizeToFit];
            rangeLabel.frame = CGRectMake(labelX, tempY + (tempLineHeight-rangeLabel.frame.size.height)/2, rangeLabel.frame.size.width, rangeLabel.frame.size.height);
            [self addSubview:rangeLabel];
            [rangeLabel release];
            
            if(i < size-1)
                tempY += (priceLabel.frame.size.height + self.verticalSpace);
            else
                tempY += priceLabel.frame.size.height;
            
            tempWidth = labelX + rangeLabel.frame.size.width;
            width = (width>=tempWidth?width:tempWidth);

            
            labelX = self.paddingLeft;
            
            

        }
        tempY += self.paddingBottom;
        self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, width, tempY);
    }
    
    [productUnit release];
    [contentArray release];
}



-(void) dealloc
{
    self.priceNumColor = nil;
    self.rangeCharColor = nil;
    [super dealloc];
}


@end
