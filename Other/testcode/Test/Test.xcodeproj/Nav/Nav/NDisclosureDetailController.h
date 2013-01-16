//
//  NDisclosureButtonController.h
//  Nav
//
//  Created by 佳 刘 on 12-9-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NDisclosureDetailController : UIViewController {
    UILabel *label;
    NSString *message;
}

@property (nonatomic,retain) IBOutlet UILabel *label;
@property (nonatomic,retain) NSString *message;

@end
