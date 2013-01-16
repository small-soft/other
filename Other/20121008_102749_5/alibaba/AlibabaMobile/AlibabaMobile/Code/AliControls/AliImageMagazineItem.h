//
//  AliImageMagazineItem.h
//  AlibabaMobile
//
//  Created by  on 12-2-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HJManagedImageV.h"
#import "HJObjManager.h"

@interface AliImageMagazineItem : UIView

@property (nonatomic, retain) IBOutlet UILabel * titleLabel;
@property (nonatomic, retain) IBOutlet HJManagedImageV * imageView;

- (void) setSubject:(NSString *) subject;

@end
