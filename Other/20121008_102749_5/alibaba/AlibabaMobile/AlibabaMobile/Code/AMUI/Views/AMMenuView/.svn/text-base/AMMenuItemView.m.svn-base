

#import "AMMenuItemView.h"
#import <QuartzCore/QuartzCore.h>
#import "ConstDef.h"
@interface AMMenuItemView()
@end

@implementation AMMenuItemView
@synthesize imageView = _imageView;
@synthesize label = _label;
@synthesize button = _button;
@synthesize imageViewBackground = _imageViewBackground;
@synthesize leftTopTagImageView = _leftTopTagImageView;
@synthesize maskImageView = _maskImageView;
- (id)init {
	self = [super init];
	
	if (self = [self initWithStyle:AMMenuItemViewStyleImageAndText]) {
        
	}
	
	return self;
}

-(id)initWithStyle:(AMMenuItemViewStyle)style{
    self = [super init];
	
	if (self) {
        switch (style) {
            case AMMenuItemViewStyleImageAndText:
            {
                NSArray *views = [[NSBundle mainBundle] loadNibNamed:@"AMMenuItemViewStyleImageAndText" owner:self options:nil];

                self = [[views objectAtIndex:0] retain];


                break;
            }
            case AMMenuItemViewStyleTextOnly:{
                NSArray *views = [[NSBundle mainBundle] loadNibNamed:@"AMMenuItemViewStyleTextOnly" owner:self options:nil];
                
                self = [[views objectAtIndex:0] retain];
                
                
                break;
            }
            case AMMenuItemViewStyleImageOnly:{
                NSArray *views = [[NSBundle mainBundle] loadNibNamed:@"AMMenuItemViewStyleImageOnly" owner:self options:nil];
                
                self = [[views objectAtIndex:0] retain];
                
                
                break;
            }
            default:
                break;
        }

	}
	
	return self;
}
- (void)dealloc {
    AM_RELEASE_SAFELY(_button);
    AM_RELEASE_SAFELY(_imageView);
    AM_RELEASE_SAFELY(_label);
    AM_RELEASE_SAFELY(_imageViewBackground);
    AM_RELEASE_SAFELY(_leftTopTagImageView);
    AM_RELEASE_SAFELY(_maskImageView);
	[super dealloc];
}

- (void)addTarget:(id)target action:(SEL)action forControlEvents:(UIControlEvents)controlEvents {
	[self.button addTarget:target action:action forControlEvents:controlEvents];
}

#pragma mark - Overriden Setters / Getters

- (void)setTag:(NSInteger)tag {
	self.button.tag = tag;
}

- (NSInteger)tag {
	return self.button.tag;
}

-(void)setLabelyPadding:(CGFloat)yPadding xPadding:(CGFloat)xPadding
{
    self.label.frame = CGRectMake(self.label.frame.origin.x + xPadding, self.label.frame.origin.y + yPadding, self.label.frame.size.width, self.label.frame.size.height);
}
@end
