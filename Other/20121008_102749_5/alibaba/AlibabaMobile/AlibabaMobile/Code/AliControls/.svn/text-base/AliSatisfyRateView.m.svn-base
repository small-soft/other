//
//  AliSatisfyRateView.m
//  AlibabaMobile
//
//  Created by  on 12-2-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliSatisfyRateView.h"
#import "UIHelp.h"

@interface AliSatisfyRateView()
{
    UIImageView * _satisfyRateIvs[5];
    UILabel * numLabel;
    float _rate;
}

@end

@implementation AliSatisfyRateView

- (id) init
{
    [super init];
    if(self){
        _rate = 0.0f;
        
        int tempX = 0;
        int tempY = 0;
        for(int i=0;i<5;i++){
            _satisfyRateIvs[i] = [[UIImageView alloc] init];
            _satisfyRateIvs[i].image =  [UIImage imageNamed:@"icon_myd0"];
            [_satisfyRateIvs[i] sizeToFit];
            _satisfyRateIvs[i].frame = CGRectMake(tempX, tempY, _satisfyRateIvs[i].frame.size.width, _satisfyRateIvs[i].frame.size.height);
            [self addSubview:_satisfyRateIvs[i]];
            
            if(i<4)
                tempX += (_satisfyRateIvs[i].frame.size.width + 1);
            else
                tempX += _satisfyRateIvs[i].frame.size.width;
        }
        numLabel = [[UILabel alloc] init];
        numLabel.backgroundColor = [UIColor clearColor];
        numLabel.font = [UIFont systemFontOfSize:12.0f];
        numLabel.textColor = [UIHelp colorWithHexString:@"0xFE7B23"];
        numLabel.text = @"0.0";
        [numLabel sizeToFit];
        tempX += 5;
        numLabel.frame = CGRectMake(tempX, tempY, numLabel.frame.size.width, numLabel.frame.size.height);
        [self addSubview:numLabel];
        tempX += numLabel.frame.size.width;
        
        self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, tempX, _satisfyRateIvs[0].frame.size.height);
    }
    return self;
}

- (void) setSatisfyRateIvs:(float)startLevel 
{
        for(int i=0; i<5;i++){
            _satisfyRateIvs[i].hidden = NO;

        }
    
        int base = 0;
        float more = 0;
        if(startLevel >=5){
            base = 5;
            more = 0;
        }else if(startLevel >= 4){
            base = 4;
            more = startLevel - 4;
        }else if(startLevel >=3){
            base = 3;
            more = startLevel - 3;
        }else if(startLevel >= 2){
            base = 2;
            more = startLevel - 2;
        }else if(startLevel >= 1){
            base = 1;
            more = startLevel - 1;
        }else{
            base = 0;
            more = startLevel;
        }
    
        for(int i=0;i<base;i++){
            _satisfyRateIvs[i].image = [UIImage imageNamed:@"icon_myd4"];
        }
    
        if(base <5){
            if(more >= 0.75)
                _satisfyRateIvs[base].image = [UIImage imageNamed:@"icon_myd3"];
            else if(more >=0.5){
                _satisfyRateIvs[base].image = [UIImage imageNamed:@"icon_myd2"];
            }else if(more >=0.25){
                _satisfyRateIvs[base].image = [UIImage imageNamed:@"icon_myd1"];
            }
        }
    
    numLabel.text = [NSString stringWithFormat:@"%.1f", startLevel];
    
}

-(void)dealloc
{
    for(int i=0; i<5; i++){
        [_satisfyRateIvs[i] release];
        
    }

    [super dealloc];
}

@end
