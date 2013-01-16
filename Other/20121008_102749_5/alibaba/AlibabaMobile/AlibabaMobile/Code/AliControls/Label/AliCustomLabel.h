//
//  AliCustomLabel.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
typedef enum
{
    VerticalAlignmentTop = 0, // default
    VerticalAlignmentMiddle,
    VerticalAlignmentBottom,
} VerticalAlignment;


@interface AliCustomLabel : UILabel
@property (nonatomic) CGFloat fontSize;
@property (nonatomic) CGFloat r;
@property (nonatomic) CGFloat g;
@property (nonatomic) CGFloat b;
@property (nonatomic) BOOL bold;
@property (nonatomic) VerticalAlignment verticalAlignment;
-(void)setupView;
@end
