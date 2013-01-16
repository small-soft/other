//
//  searchBarSelectView.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliCustomerSearchBarSelectView.h"
#import "AliCustomerSearchViewDef.h"
@implementation AliCustomerSearchBarSelectView
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
        case SEARCH_CONTACT:
            self.content.text=@"联系人";
            break;
        case SEARCH_TELE:   
        default:
             self.content.text=@"电话";
            break;
    }
    
}

+(id)createView
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliCustomerSearchBarSelectView" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliCustomerSearchBarSelectView class]])
        {
            return  (AliCustomerSearchBarSelectView *)oneObject;
        }
    }
    return nil;
}

- (void)dealloc {
    [_content release];
    [_identifyImage release];
    [super dealloc];
}
@end
