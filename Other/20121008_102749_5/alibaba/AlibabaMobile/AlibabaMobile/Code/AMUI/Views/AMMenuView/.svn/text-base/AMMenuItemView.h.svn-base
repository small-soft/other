

#import <UIKit/UIKit.h>
#import "HJManagedImageV.h"
typedef enum {
    AMMenuItemViewStyleImageAndText,
    AMMenuItemViewStyleTextOnly,
    AMMenuItemViewStyleImageOnly
}AMMenuItemViewStyle;

@interface AMMenuItemView : UIView {
    HJManagedImageV * _imageView;
    UIImageView * _imageViewBackground;
    UILabel * _label;
    UIButton * _button;
    UIImageView * _leftTopTagImageView;
    UIImageView * _maskImageView;
}
@property (retain, nonatomic) IBOutlet HJManagedImageV *imageView;
@property (retain, nonatomic) IBOutlet UILabel *label;
@property (retain, nonatomic) IBOutlet UIButton *button;
@property (retain, nonatomic) IBOutlet UIImageView * imageViewBackground;
@property (retain, nonatomic) IBOutlet UIImageView * leftTopTagImageView;
@property (retain, nonatomic) IBOutlet UIImageView * maskImageView;
/**
 * Supports UIButton-style adding targets
 */
- (void)addTarget:(id)target action:(SEL)action forControlEvents:(UIControlEvents)controlEvents;
-(id)initWithStyle:(AMMenuItemViewStyle)style;
-(void)setLabelyPadding:(CGFloat)yPadding xPadding:(CGFloat)xPadding;
@end
