//
//  PKCustomPickerViewController.m
//  Pick
//
//  Created by 佳 刘 on 12-9-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "PKCustomPickerViewController.h"
#import <AudioToolbox/AudioServices.h>

@interface PKCustomPickerViewController ()

@end

@implementation PKCustomPickerViewController
@synthesize picker = _picker;
@synthesize winLabel = _winLabel;
@synthesize col1 = _col1;
@synthesize col2 = _col2;
@synthesize col3 = _col3;
@synthesize col4 = _col4;
@synthesize col5 = _col5;
@synthesize button = _button;


#pragma - mark
#pragma mark vc lifecycle
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    UIImage *seven = [UIImage imageNamed:@"seven.png"];
    UIImage *bar = [UIImage imageNamed:@"bar.png"];
    UIImage *crown = [UIImage imageNamed:@"crown.png"];
    UIImage *cherry = [UIImage imageNamed:@"cherry.png"];
    UIImage *lemon = [UIImage imageNamed:@"lemon.png"];
    UIImage *apple = [UIImage imageNamed:@"apple.png"];
    
    for (int i = 1;i<=5; i++) {
        UIImageView *sevenView = [[[UIImageView alloc]initWithImage:seven]autorelease];
        UIImageView *barView = [[[UIImageView alloc]initWithImage:bar]autorelease];
        UIImageView *crownView = [[[UIImageView alloc]initWithImage:crown]autorelease];
        UIImageView *cherryView = [[[UIImageView alloc]initWithImage:cherry]autorelease];
        UIImageView *lemonView = [[[UIImageView alloc]initWithImage:lemon]autorelease];
        UIImageView *appleView = [[[UIImageView alloc]initWithImage:apple]autorelease];
        
        NSArray *imageViewArray = [NSArray arrayWithObjects:sevenView,barView,crownView,cherryView,lemonView,appleView, nil];
        
        NSString *fieldName = [NSString stringWithFormat:@"col%d",i];
        [self setValue:imageViewArray forKey:fieldName];
    }
    
    // 随机数生成器
    srandom(time(NULL));
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
    self.picker = nil;
    self.winLabel = nil;
    self.col1 = nil;
    self.col2 = nil;
    self.col3 = nil;
    self.col4 = nil;
    self.col5 = nil;
    self.button = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma - mark
#pragma mark action
- (void)spin {
    BOOL win = NO;
    int numInRow = 1;
    int lastVal = -1;
    
    for (int i = 0; i < 5; i ++) {
        int newValue = random() % [self.col1 count];
        
        if (newValue == lastVal) {
            numInRow ++;
        } else {
            numInRow = 1;
        }
        
        lastVal = newValue;
        [self.picker selectRow:newValue inComponent:i animated:YES];
        [self.picker reloadComponent:i];
        
        if (numInRow >= 3) {
            win = YES;
        } else {
            self.winLabel.text = @"";
        }
    }
    
    self.button.hidden = YES;
    NSString *path = [[NSBundle mainBundle]pathForResource:@"crunch" ofType:@"wav"];
    SystemSoundID soundId;
    AudioServicesCreateSystemSoundID((CFURLRef)[NSURL fileURLWithPath:path], &soundId);
    AudioServicesPlaySystemSound(soundId);
    
    if (win) {
        [self performSelector:@selector(playWinSound) withObject:nil afterDelay:.5];
    }else {
        [self performSelector:@selector(showButton) withObject:nil afterDelay:.5];
    }
    
    self.winLabel.text =@"";
}

- (void) showButton {
    self.button.hidden = NO;
}

- (void) playWinSound {
    NSString *path = [[NSBundle mainBundle]pathForResource:@"win" ofType:@"wav"];
    SystemSoundID soundId;
    AudioServicesCreateSystemSoundID((CFURLRef)[NSURL fileURLWithPath:path], &soundId);
    AudioServicesPlaySystemSound(soundId);
    self.winLabel.text = @"Win!";
    [self performSelector:@selector(showButton) withObject:nil afterDelay:1.5];
}

#pragma - mark
#pragma mark picker datea source methods
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 5;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    switch (component) {
        case 0:
            return [self.col1 count];
            break;
        case 1:
            return [self.col2 count];
            break;
        case 2:
            return [self.col3 count];
            break;
        case 3:
            return [self.col4 count];
            break;
        default:
            return [self.col5 count];
            break;
    }
}

-(UIView *)pickerView:(UIPickerView *)pickerView viewForRow:(NSInteger)row forComponent:(NSInteger)component reusingView:(UIView *)view {
    NSString *arrayName = [NSString stringWithFormat:@"col%d",component+1];
    NSArray *array = [self valueForKey:arrayName];
    
    return [array objectAtIndex:row];
}
@end
