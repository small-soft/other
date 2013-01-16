//
//  AliCreditFileTitleView.m
//  AlibabaMobile
//
//  Created by  on 12-2-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliCreditFileTitleView.h"
#import "AMCreditResult.h"
#import "AMCompanyDetail.h"
#import "AMCreditSummary.h"
#import "AMCreditGuarantee.h"
#import "AMCreditRealAuth.h"
#import "AMDataDictConstants.h"
#import "AliImageControlFactory.h"
#import "UIHelp.h"

@interface AliCreditFileTitleView()

@property (nonatomic,retain) HJObjManager *objMan;

-(void)objManInit;

@end

@implementation AliCreditFileTitleView

@synthesize objMan = _objMan;

- (id) initWithFrame:(CGRect)frame
{
    [super initWithFrame:frame];
    [self objManInit];
    return self;
}

-(void)objManInit
{
    _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcache/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	_objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
    
}

- (void) setContentDateEx:(AMCreditResult *) creditResult compnayDetail:(AMCompanyDetail *) companyDetail
{
    int tempX = 15;
    int tempY = 10;
    
//    if(companyDetail.name != nil){
//        UILabel *  nameLabel = [[UILabel alloc] init];
//        nameLabel.text = companyDetail.name;
//        nameLabel.backgroundColor = [UIColor clearColor];
//        nameLabel.textColor= [UIColor blackColor];
//        nameLabel.font = [UIFont boldSystemFontOfSize:14.0f];
//        [nameLabel sizeToFit];
//        nameLabel.frame = CGRectMake(tempX, tempY, nameLabel.frame.size.width, nameLabel.frame.size.height);
//        tempY += (nameLabel.frame.size.height+10);
//        [self addSubview:nameLabel];
//        [nameLabel release];
//    }
    
//    NSString * memberType = companyDetail.memberType;
//    if(memberType != nil){
//        if([memberType isEqualToString:MEMBER_TYPE_PERSON]){
//            AliImageButton * img = [[AliImageControlFactory sharedInstance] getImageButtonWithType:REAL_AUTH_PERSON_ICON];
//            img.frame = CGRectMake(tempX, tempY, img.frame.size.width, img.frame.size.height);
//            [self addSubview:img];
//            tempX +=(img.frame.size.width + 10);
//            
//            UILabel *  desLabel = [[UILabel alloc] init];
//            desLabel.text = @"通过个人实名认证";
//            desLabel.backgroundColor = [UIColor clearColor];
//            desLabel.textColor= [UIHelp colorWithHexString:@"0x2B4D86"];
//            desLabel.font = [UIFont systemFontOfSize:14.0f];
//            [desLabel sizeToFit];
//            desLabel.frame = CGRectMake(tempX, tempY, desLabel.frame.size.width, desLabel.frame.size.height);
//            tempY += (desLabel.frame.size.height+10);
//            [self addSubview:desLabel];
//            [desLabel release];
//        }else if([memberType isEqualToString:MEMBER_TYPE_FREE]){
//            //do nothings
//        }else{
//            AliImageButton * img = [[AliImageControlFactory sharedInstance] getImageButtonWithType:REAL_AUTH_COMPANY_ICON];
//            img.frame = CGRectMake(tempX, tempY, img.frame.size.width, img.frame.size.height);
//            [self addSubview:img];
//            tempX +=(img.frame.size.width + 10);
//            
//            UILabel *  desLabel = [[UILabel alloc] init];
//            desLabel.text =  [NSString stringWithFormat:@"通过 %@ 认证", creditResult.realAuth.avProvider];
//            desLabel.backgroundColor = [UIColor clearColor];
//            desLabel.textColor= [UIHelp colorWithHexString:@"0x2B4D86"];
//            desLabel.font = [UIFont systemFontOfSize:14.0f];
//            [desLabel sizeToFit];
//            desLabel.frame = CGRectMake(tempX, tempY, desLabel.frame.size.width, desLabel.frame.size.height);
//            tempY += (desLabel.frame.size.height+10);
//            [self addSubview:desLabel];
//            [desLabel release];
//
//        }
//        tempX = 15;
//    }
    
   if(creditResult.summary != nil
       && creditResult.summary.tpLogo != nil){
        HJManagedImageV * chengBaoIv = [[HJManagedImageV alloc] initWithFrame:CGRectMake(tempX-10, tempY-7,70, 30)];

        chengBaoIv.backgroundColor = [UIColor clearColor];
       chengBaoIv.contentMode = UIViewContentModeScaleToFill;
        chengBaoIv.imageView.contentMode = UIViewContentModeScaleToFill;
        chengBaoIv.url = [NSURL URLWithString:creditResult.summary.tpLogo];
       
        [self.objMan manage:chengBaoIv];
        
        tempX += (chengBaoIv.frame.size.width );
        [self addSubview:chengBaoIv];
        [chengBaoIv release];
    }
    
    UILabel *  label0 = [[UILabel alloc] init];
    label0.text = @"第";
    label0.backgroundColor = [UIColor clearColor];
    label0.textColor= [UIColor blackColor];
    label0.font = [UIFont systemFontOfSize:14.0f];
    [label0 sizeToFit];
    label0.frame = CGRectMake(tempX, tempY, label0.frame.size.width, label0.frame.size.height);
    tempX += label0.frame.size.width;
   
    UILabel *  label1 = [[UILabel alloc] init];
    label1.text = creditResult.summary.tpYear.stringValue;
    label1.backgroundColor = [UIColor clearColor];
    label1.textColor= [UIHelp colorWithHexString:@"0xCC0000"];
    label1.font = [UIFont boldSystemFontOfSize:14.0f];
    [label1 sizeToFit];
    label1.frame = CGRectMake(tempX, tempY, label1.frame.size.width, label1.frame.size.height);
    tempX += label1.frame.size.width;
     int lineHeight = label1.frame.size.height;
    [self addSubview:label1];
    [label1 release];
    
    label0.frame = CGRectMake(label0.frame.origin.x, tempY + (lineHeight - label0.frame.size.height), label0.frame.size.width, label0.frame.size.height);
    [self addSubview:label0];
    [label0 release];
    
    
    UILabel *  label2 = [[UILabel alloc] init];
    label2.text = @"年";
    label2.backgroundColor = [UIColor clearColor];
    label2.textColor= [UIColor blackColor];
    label2.font = [UIFont systemFontOfSize:14.0f];
    [label2 sizeToFit];
    label2.frame = CGRectMake(tempX, tempY + (lineHeight - label2.frame.size.height), label2.frame.size.width, label2.frame.size.height);
    tempX += (label2.frame.size.width + 30);
    [self addSubview:label2];
   
    [label2 release];
    
    UILabel *  label3 = [[UILabel alloc] init];
    label3.text = @"诚信指数：";
    label3.backgroundColor = [UIColor clearColor];
    label3.textColor= [UIHelp colorWithHexString:@"0x999999"];
    label3.font = [UIFont systemFontOfSize:14.0f];
    [label3 sizeToFit];
    label3.frame = CGRectMake(tempX, tempY + (lineHeight - label3.frame.size.height), label3.frame.size.width, label3.frame.size.height);
    tempX += (label3.frame.size.width);
    [self addSubview:label3];
    [label3 release];
    
    int score = creditResult.summary.tpScore.intValue;
    NSString * scoreStr = [NSString stringWithFormat:@"%@" ,(score > 0?[NSString stringWithFormat:@"%d", score ]:@"-")];
    UILabel *  label4 = [[UILabel alloc] init];
    label4.text = scoreStr;
    label4.backgroundColor = [UIColor clearColor];
    label4.textColor= [UIHelp colorWithHexString:@"0x000000"];
    label4.font = [UIFont systemFontOfSize:14.0f];
    [label4 sizeToFit];
    label4.frame = CGRectMake(tempX, tempY + (lineHeight - label4.frame.size.height), label4.frame.size.width, label4.frame.size.height);
    tempX =15;
    [self addSubview:label4];
    tempY +=(label4.frame.size.height);
    [label4 release];
//    
//    if(creditResult.guarantee.totalCreditMoney != nil
//       && creditResult.guarantee.totalCreditMoney.floatValue > 0){
//        tempY += 10;
//        
//        AliImageButton * chengbaoIv = [[AliImageControlFactory sharedInstance] getImageButtonWithType:CHENG_BAO_ICON];
//        chengbaoIv.frame = CGRectMake(tempX, tempY, chengbaoIv.frame.size.width, chengbaoIv.frame.size.height);
//        [self addSubview:chengbaoIv];
//        tempX += (chengbaoIv.frame.size.width + 10);
//        
//        UILabel *  label5 = [[UILabel alloc] init];
//        label5.text = [NSString stringWithFormat:@"诚信保障  ¥%@", creditResult.guarantee.totalCreditMoney];
//        label5.backgroundColor = [UIColor clearColor];
//        label5.textColor= [UIHelp colorWithHexString:@"0x2B4D86"];
//        label5.font = [UIFont systemFontOfSize:14.0f];
//        [label5 sizeToFit];
//        label5.frame = CGRectMake(tempX, tempY , label5.frame.size.width, label5.frame.size.height);
//        [self addSubview:label5];
//        tempY +=(label5.frame.size.height);
//        [label5 release];
//    }
    
   
     
    self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, tempY + 10);
    
//    UIImageView *seceptorLine = [[UIImageView alloc] init ];
//    seceptorLine.frame = CGRectMake(0, self.frame.size.height-1, 320, 1);
//    seceptorLine.backgroundColor = [UIColor clearColor];
//    seceptorLine.image = [UIImage imageNamed:@"line_gray"];
//    [self addSubview:seceptorLine];
}

- (void) dealloc
{
    [_objMan release];
    
    [super dealloc];
}


@end
