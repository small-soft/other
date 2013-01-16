//
//  GraphNode.h
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-10.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum {
    MyUIButtonTypeCustom = 0,
    MyUIButtonTypeRoundedRect,
    MyUIButtonTypeDetailDisclosure,
    MyUIButtonTypeInfoLight,
    MyUIButtonTypeInfoDark,
    MyUIButtonTypeContactAdd,
} MyUIButtonType;

@interface GraphNode : UIButton
{
    NSInteger id_;
    NSString *name;
    NSString *lableInfo;
    MyUIButtonType mybuttonType;
}
@property (nonatomic,assign)NSInteger id_;
@property (nonatomic,retain)NSString *name;
@property (nonatomic,retain)NSString *lableInfo;
@property (nonatomic, assign) MyUIButtonType mybuttonType;


- (id)initWithID:(NSInteger)newID name:(NSString *)newName rect:(CGRect)frame;
- (void)btAction:(id)sende;
- (id)initWithFrame:(CGRect)frame;
@end
