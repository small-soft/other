//
//  AliSearchView.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliCustomerSearchView.h"

#import "AliCustomerSearchViewDef.h"
#import "AliCustomerSearchBarSelectView.h"
#import "searchBarEditView.h"
#import "searchBarCancelView.h"
#import "AMCustomerMyCustomerViewController.h"
#define SEARCHBAR_START_X 10.0
#define SEARCHBAR_END_X 10.0


@interface AliCustomerSearchView()
@property (nonatomic,retain)UIImageView*backgroundView;
@property (nonatomic,retain)AliCustomerSearchBarSelectView*selectedView;
@property (nonatomic,retain)searchBarEditView*editView;
@property (nonatomic,retain)AliTableViewMyCustomerPickerView*searchPicker;
@property (nonatomic)BOOL editing;

@end

@implementation AliCustomerSearchView
@synthesize delegate=_delegate;
@synthesize backgroundView = _backgroundView;
@synthesize selectedView=_selectedView;
@synthesize searchPicker=_searchPicker;
@synthesize editView=_editView;
@synthesize editing=_editing;
@synthesize mMyCustomerSelectionView = _mMyCustomerSelectionView;
@synthesize pickerContent = _pickerContent;

-(void)dealloc
{
    [_delegate release];
    [_backgroundView release];
    [_selectedView release];
    [_editView release];
    [_searchPicker release];
    [_mMyCustomerSelectionView release];
    [_pickerContent release];
    [super dealloc];
}

-(UIImageView*)backgroundView
{
    if (!_backgroundView) {

        _backgroundView = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"bg_searchbg2.png"]];
        [_backgroundView sizeToFit];
        _backgroundView.frame = CGRectMake(0.0, 0.0, _backgroundView.frame.size.width, _backgroundView.frame.size.height);
    }
    return _backgroundView;
}

-(AliCustomerSearchBarSelectView*)selectedView
{
    if (!_selectedView) {
        _selectedView = [AliCustomerSearchBarSelectView createView];
        [_selectedView addTarget:self action:@selector(selectViewUpInsideAction:)  forControlEvents:UIControlEventTouchUpInside];
        _selectedView.selectedState = SEARCH_COMPANY;
        _selectedView.frame = CGRectMake(SEARCHBAR_START_X, 0.0, _selectedView.frame.size.width, _selectedView.frame.size.height);
    }
    return _selectedView;
}
-(searchBarEditView*)editView
{
    if (!_editView) {
        _editView = [searchBarEditView createView];  
        [_editView.editTextField addTarget:self action:@selector(searchBarEditViewEditBegin:) forControlEvents:UIControlEventEditingDidBegin];
        [_editView.editTextField addTarget:self action:@selector(searchBarEditViewDidEnd:) forControlEvents:UIControlEventEditingDidEndOnExit];
        [_editView.editTextField addTarget:self action:@selector(searchBarEditViewEditChanged:) forControlEvents:UIControlEventEditingChanged];
        [_editView.deleteButton addTarget:self action:@selector(deleteButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    }
    CGFloat startX=SEARCHBAR_START_X+self.selectedView.frame.size.width;
    CGFloat editViewWidth = 0;

    editViewWidth = self.frame.size.width-SEARCHBAR_END_X-startX;
    _editView.frame = CGRectMake(startX, 0.0, editViewWidth, _editView.frame.size.height);

    return _editView;
}

-(AliTableViewMyCustomerPickerView*)searchPicker
{
    
    if (!_searchPicker) {
        
        _searchPicker = [[AliTableViewMyCustomerPickerView alloc] initWithGroupArray:[[NSMutableArray alloc] initWithObjects: @"公司",@"联系人",@"电话",nil]];
        [_searchPicker reloadData];
        _searchPicker.hidden = YES;
        [self.superview addSubview:_searchPicker];
        _searchPicker.frame = CGRectMake(5, self.frame.origin.y+self.frame.size.height-5, _searchPicker.frame.size.width-5, _searchPicker.frame.size.height);
        _searchPicker.delegatePicker = self;
        _searchPicker.buttonPressType = 3;
    }
    
    return _searchPicker;
    
}

-(void)setDelegate:(NSObject<AliCustomerSearchViewDelegate> *)delegate
{
    if (!_delegate) {
        _delegate=delegate;
        
      } 
}
-(void)setEditing:(BOOL)editing
{
    _editing = editing;
    [UIView beginAnimations:@"filpping" context:nil];
    [UIView setAnimationDuration:0.5];
    self.editView.hidden=NO;

    [UIView commitAnimations];
}

-(void)awakeFromNib
{
    [super awakeFromNib];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil]; 
    [self setupViews];
}
-(void)setupViews
{
    [self addSubview:self.backgroundView];
    [self addSubview:self.selectedView];
    [self addSubview:self.editView]; 
}
-(void)editBecomeFirstResponder
{
    [self.editView.editTextField becomeFirstResponder];
}
            
-(void)gotoSearch:(NSString*)content selected:(NSUInteger)selected
{
    if ([self.delegate respondsToSelector:@selector(searchBarEditViewDidEnd:content:selected:pickerContent:)])
    {
        [self.delegate searchBarEditViewDidEnd:self content:content selected:self.selectedView.selectedState pickerContent:self.pickerContent];
    }
    
}




/*
 ACTION
 */
-(IBAction)selectViewUpInsideAction:(id)sender
{
    NSLog(@"select sender......");
    if (self.searchPicker.hidden) {
        self.searchPicker.hidden = NO;
    
        
        self.mMyCustomerSelectionView = [[UIView alloc] initWithFrame:CGRectMake(0, 80, 320, 360)];  
        self.mMyCustomerSelectionView.backgroundColor = [UIColor darkGrayColor];
        self.mMyCustomerSelectionView.alpha = 0.6;
    [self.superview insertSubview:self.mMyCustomerSelectionView belowSubview:self.searchPicker];
        
    }
    else {
        
        [self.mMyCustomerSelectionView removeFromSuperview];
        self.searchPicker.hidden = YES;
    }
}

-(IBAction)searchBarEditViewEditBegin:(id)sender
{
    self.editing=YES;
    self.searchPicker.hidden = YES;

    if ([self.delegate respondsToSelector:@selector(searchBarEditViewEditBegin:)])
    {
        [self.delegate searchBarEditViewEditBegin:self];
    }
}
-(IBAction)searchBarEditViewDidEnd:(UITextField*)sender
{
    [self gotoSearch:sender.text selected:self.selectedView.selectedState];
//    self.editView.editTextField.text=@"";
    self.editing=NO;
    
}
-(IBAction)searchBarEditViewEditChanged:(UITextField*)sender
{
    [self.editView refreshInputState];
}

-(void)keyDisappearForce{
    [self.editView.editTextField resignFirstResponder];
    if(self.mMyCustomerSelectionView){
        [self.mMyCustomerSelectionView removeFromSuperview];
    }
    self.searchPicker.hidden = YES;
}
- (IBAction)cancelButtonTouchUpInside:(id)sender {
    
    self.editing = NO;
    self.editView.editTextField.text = @"";
    [self.editView.editTextField resignFirstResponder];
    self.searchPicker.hidden = YES;
//    self.searchHistory.hidden = YES;

    if ([self.delegate respondsToSelector:@selector(searchBarEditCancel:)])
    {
        [self.delegate searchBarEditCancel:self];
    }
}
- (IBAction)deleteButtonPressed:(id)sender {
    self.editView.editTextField.text=@"";
}

- (void)keyboardWillShow:(NSNotification *)notification  
{  

    self.searchPicker.frame = CGRectMake(SEARCHBAR_START_X, self.frame.origin.y+self.frame.size.height, self.searchPicker.frame.size.width, self.searchPicker.frame.size.height);

}  
//delegate
- (void)searchHistoryTable:(searchHistoryTable *)tableView didSelectRow:(NSString *)content
{
    [self gotoSearch:content selected:self.selectedView.selectedState];
}
- (void)searchHistoryTable:(searchHistoryTable *)tableView rowEdit:(NSString *)content
{
    self.editView.editTextField.text = content;
}

-(void)pickerView:(AliTableViewMyCustomerPickerView*)picker selected:(NSUInteger)selectedPicker content:(NSString*)content type:(NSUInteger)type

{
    if(self.mMyCustomerSelectionView){
      [self.mMyCustomerSelectionView removeFromSuperview];    
    }
    self.selectedView.selectedState = selectedPicker;
    self.searchPicker.hidden = YES;
    self.pickerContent = content;
}
@end
