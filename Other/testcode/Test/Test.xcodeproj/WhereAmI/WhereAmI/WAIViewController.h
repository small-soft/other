//
//  WAIViewController.h
//  WhereAmI
//
//  Created by 佳 刘 on 12-10-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

@interface WAIViewController : UIViewController <CLLocationManagerDelegate> {
    CLLocationManager *locationManager;
    CLLocation *startingPoint;
    UILabel *latitudeLabel;
    UILabel *longitudeLabel;
    UILabel *horizontalAccuracyLabel;
    UILabel *altitudeLabel;
    UILabel *vericalAccuracyLabel;
    UILabel *distanceTraveledLabel;
}

@property (nonatomic,retain) CLLocationManager *locationManager;
@property (nonatomic,retain) CLLocation *startingPoint;
@property (nonatomic,retain) IBOutlet UILabel *latitudeLabel;
@property (nonatomic,retain) IBOutlet UILabel *longitueLabel;
@property (nonatomic,retain) IBOutlet UILabel *altitudeLabel;
@property (nonatomic,retain) IBOutlet UILabel *verticalAccuracyLabel;
@property (nonatomic,retain) IBOutlet UILabel *distanceTraveledLabel;
@property (nonatomic,retain) IBOutlet UILabel *horizontalAccuracyLabel;
@end
