//
//  searchBarEditViewWithImage.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-21.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "searchBarEditViewWithImage.h"

@implementation searchBarEditViewWithImage

@synthesize deleteButton = _deleteButton;
@synthesize editTextField = _editTextField;
@synthesize backgroundImage = _backgroundImage;


-(void)setFrame:(CGRect)frame
{
    [super setFrame:frame];
    self.deleteButton.frame = CGRectMake(self.frame.size.width - self.deleteButton.frame.size.width-5, self.deleteButton.frame.origin.y,self.deleteButton.frame.size.width, self.deleteButton.frame.size.height);
    self.editTextField.frame = CGRectMake(self.editTextField.frame.origin.x, self.editTextField.frame.origin.y,(self.deleteButton.frame.origin.x - self.editTextField.frame.origin.x-1), self.editTextField.frame.size.height);
}

-(void)refreshInputState
{
    if (self.editTextField.text==nil||self.editTextField.text.length ==0) {
        
        [self.deleteButton setHidden:YES];
        
    }
    else
    {
        [self.deleteButton setHidden:NO];
    }
}

+(id)createView
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"searchBarEditViewWithImage" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[searchBarEditViewWithImage class]])
        {
            searchBarEditViewWithImage *obj = (searchBarEditViewWithImage *)oneObject;
            [obj setupView];
            return  obj;
        }
    }
    return nil;
}

-(void)setupView
{
    UIImage *image = [UIImage imageNamed:@"search_bg"];
    image = [ image stretchableImageWithLeftCapWidth: image.size.width/2 topCapHeight: image.size.height/2 ];
    self.backgroundImage.frame = CGRectMake(0.0, 6,self.frame.size.width, 31);
    self.backgroundImage.image = image;
    self.editTextField.textColor = [UIColor colorWithRed:99/255.0 green:99/255.0 blue:99/255.0 alpha:1.0];
    //    CGSize itemSize = self.backgroundImage.frame.size;
    //    UIGraphicsBeginImageContext(itemSize);
    //    CGRect imageRect = CGRectMake(0.0, 0.0, itemSize.width, itemSize.height);
    //    //[imageTmp drawInRect:imageRect];
    //    [image drawInRect:imageRect];
    //    self.backgroundImage.image = UIGraphicsGetImageFromCurrentImageContext();
    //    UIGraphicsEndImageContext();
    //    [self addSubview:self.backgroundImage];
}

- (void)dealloc {
    [_deleteButton release];
    [_editTextField release];
    [_backgroundImage release];
    [super dealloc];
}
@end
