//
//  TEViewController.h
//  TouchExplorer
//
//  Created by 佳 刘 on 12-10-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface TEViewController : UIViewController {
    UILabel *messageLabel;
    UILabel *tapsLabel;
    UILabel *touchesLabel;
}

@property (nonatomic,retain) IBOutlet UILabel *messageLabel;
@property (nonatomic,retain) IBOutlet UILabel *tapsLabel;
@property (nonatomic,retain) IBOutlet UILabel *touchesLabel;

- (void)updateLabelsFromTouches:(NSSet *)touches;

@end
