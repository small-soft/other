//
//  searchBarSelectView.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "searchBarSelectView.h"
#import "searchViewDef.h"
@implementation searchBarSelectView
@synthesize content=_content;
@synthesize identifyImage = _identifyImage;
@synthesize selectedState=_selectedState;

-(void)setSelectedState:(NSUInteger)selectedState
{
    _selectedState = selectedState;
    switch (selectedState) {
        case SEARCH_COMPANY:
            self.content.text=@"公司";
            break;
        case SEARCH_PRICE:
            self.content.text=@"价格";
            break;
        case SEARCH_PRODUCT:   
        default:
             self.content.text=@"产品";
            break;
    }
    
}


+(id)createView
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"searchBarSelectView" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[searchBarSelectView class]])
        {
            searchBarSelectView *obj = (searchBarSelectView *)oneObject;
            [obj setupView];
            return  obj;
        }
    }
    return nil;
}

-(void)setupView
{
    self.content.font = [UIFont systemFontOfSize:14.0]; 
    self.content.textColor = [UIColor colorWithRed:51/255.0 green:51/255.0 blue:51/255.0 alpha:1.0];
}

- (void)dealloc {
    [_content release];
    [_identifyImage release];
    [super dealloc];
}
@end
