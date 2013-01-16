//
//  AMOfferPropertiesViewController.m
//  AlibabaMobile
//
//  Created by mardin partytime on 2/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AMOfferPropertiesViewController.h"
#import "AMOfferDetail.h"
#import "UIHelp.h"
#import "KeyValueObject.h"
#import "AliKeyValueMapView.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"

@implementation AMOfferPropertiesViewController

@synthesize  mMainScrollView;


- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

-(void) dealloc
{
    [mOfferDetail release];
    [mMainScrollView release];
    
    [super dealloc];
}

- (void) viewWillAppear:(BOOL)animated
{
    [AMLogUtils appendLog:APP_PRD_DETAL_FIVE];
}

- (void)viewDidLoad
{
    [super viewDidLoad];

     mOfferDetail = [self.dataDict objectForKey:TAB_VIEW_DATA_OFFER_DETAIL];
    
    if(mOfferDetail != nil 
       && mOfferDetail.featureAttributes != nil 
       && mOfferDetail.featureAttributes.count > 0){
        
        NSMutableArray * keyValueArray = [[NSMutableArray alloc]init];
        int size = mOfferDetail.featureAttributes.count;
        for(int i=0; i< size; i++){
            KeyValueObject * obj = [[KeyValueObject alloc]init];
            obj.key = ((AMFeatureAttribute *)[mOfferDetail.featureAttributes objectAtIndex:i]).name;
            obj.value =  [self getAttributesString:(((AMFeatureAttribute *)[mOfferDetail.featureAttributes objectAtIndex:i]).values)];
            
            [keyValueArray addObject:obj];
            [obj release];
        }
        AliKeyValueMapView * mappingView = [[AliKeyValueMapView alloc] init];
        [mappingView setContentArray:keyValueArray maxKeyLabelString:@"无个汉子宽"];
        mappingView.frame = CGRectMake(0, 0, mappingView.frame.size.width, mappingView.frame.size.height);
        [self.mMainScrollView addSubview:mappingView];
        self.mMainScrollView.contentSize = mappingView.frame.size;
        [mappingView release];
        [keyValueArray release];
        
    }
}

-(NSString *) getAttributesString:(NSArray *) attributes
{
    if(attributes != nil
       && attributes.count > 0){
        
        NSString * str = [[[NSString alloc] initWithString: @""] autorelease];
        int size = attributes.count;
        for(int i=0;i<size;i++){
            str = [str stringByAppendingString:((NSString *)[attributes objectAtIndex:i])];
            if(i < size -1)
                str = [str stringByAppendingString:@","];
        }
        NSLog(@"attributes %@", str);
        return str;
    }else{
        return @"";
    }
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
