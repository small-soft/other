//
//  AliTitleCellView.h
//  AlibabaMobile
//
//  Created by  on 12-2-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AliTitleCellView : UIView

@property (nonatomic, retain) UILabel * titleLabel;
@property (nonatomic, retain) UILabel * subTitleLabel;
@property (nonatomic, assign) int paddingLeft;

- (id)initWithFrame:(CGRect)frame;
- (void) setTitle:(NSString *)title;

- (void) setPaddingLeft:(int)paddingLeft;
- (void) setSubTitle:(NSString *)subTitle;


@end
