//
//  NPresidentDetailController.m
//  Nav
//
//  Created by 佳 刘 on 12-9-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NPresidentDetailController.h"
#import "NPresident.h"

@implementation NPresidentDetailController
@synthesize president;
@synthesize fieldLabels;
@synthesize tempValues;
@synthesize textFieldBeingEdited;

#pragma mark -
#pragma mark vc lifecycle
-(void)viewDidLoad {
    NSArray *array = [NSArray arrayWithObjects:@"Name:",@"From:",@"To:",@"Party:", nil];
    self.fieldLabels = array;
    
    UIBarButtonItem *cancelButton = [[UIBarButtonItem alloc]initWithTitle:@"Cancel" style:UIBarButtonItemStylePlain target:self action:@selector(cancel:)];
    self.navigationItem.leftBarButtonItem = cancelButton;
    
    UIBarButtonItem *saveButton = [[UIBarButtonItem alloc]initWithTitle:@"save" style:UIBarButtonItemStyleDone target:self action:@selector(save:)];
    self.navigationItem.rightBarButtonItem = saveButton;
    
    NSMutableDictionary *dict = [[[NSMutableDictionary alloc]init]autorelease];
    self.tempValues = dict;
    
    [super viewDidLoad];
}

-(void)dealloc {
    [textFieldBeingEdited release];
    [tempValues release];
    [president release];
    [fieldLabels release];
    
    [super dealloc];
}

#pragma mark -
#pragma mark actions
-(void)cancel:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}

-(void)save:(id)sender {
    if (textFieldBeingEdited != nil) {
        NSNumber *tagAsNum = [NSNumber numberWithInt:textFieldBeingEdited.tag];
        [tempValues setObject:textFieldBeingEdited.text forKey:tagAsNum];
    }
    
    for (NSNumber *key in [tempValues allKeys]) {
        switch ([key intValue]) {
            case kNameRowIndex:
                president.name = [tempValues objectForKey:key];
                break;
            case kFromYearRowIndex:
                president.fromYear = [tempValues objectForKey:key];
                break;
            case kToYearRowIndex:
                president.toYear = [tempValues objectForKey:key];
                break;
            case kPartyRowIndex:
                president.party = [tempValues objectForKey:key];
                break;
            default:
                break;
        }
    }
    
    [self.navigationController popViewControllerAnimated:YES];
    
    NSArray *allControllers = self.navigationController.viewControllers;
    UITableViewController *parent = [allControllers lastObject];
    [parent.tableView reloadData];
}

-(void)textFieldDone:(id)sender {
    [sender resignFirstResponder];
}

#pragma mark -
#pragma mark table view delegate & data source
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return kNumberOfEditableRows;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *identifier = @"PresidentDetailCellIdentifier";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    
    if (cell == nil) {
        cell = [[[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:identifier]autorelease];
        UILabel *label = [[UILabel alloc]initWithFrame:CGRectMake(10, 10, 75, 25)];
        label.textAlignment = UITextAlignmentRight;
        label.tag = kLabelTag;
        label.font = [UIFont boldSystemFontOfSize:14];
        [cell.contentView addSubview:label];
        
        UITextField *textField = [[[UITextField alloc]initWithFrame:CGRectMake(90, 12, 200, 25)]autorelease];
        textField.clearsOnBeginEditing = NO;
        [textField setDelegate:self];
        textField.returnKeyType = UIReturnKeyDone;
        [textField addTarget:self action:@selector(textFieldDone:) forControlEvents:UIControlEventEditingDidEndOnExit];
        [cell.contentView addSubview:textField];
    }

UILabel *label = (UILabel *)[cell viewWithTag:kLabelTag];
UITextField *textField = nil;
for(UIView *oneView in cell.contentView.subviews) {
    if([oneView isMemberOfClass:[UITextField class]]){
        textField = (UITextField *)oneView;
    }
}
label.text = [fieldLabels objectAtIndex:indexPath.row];

NSNumber *rowAsNum = [[[NSNumber alloc]initWithInt:indexPath.row]autorelease];
switch(indexPath.row) {
        
    case kNameRowIndex:
        if([[tempValues allKeys]containsObject:rowAsNum]){
            textField.text = [tempValues objectForKey:rowAsNum];
        }else {
            textField.text = self.president.name;
        }
        break;
    case kFromYearRowIndex:
        if([[tempValues allKeys]containsObject:rowAsNum]){
            textField.text = [tempValues objectForKey:rowAsNum];
        }else {
            textField.text = self.president.fromYear;
        }
        break;
    case kToYearRowIndex:
        if([[tempValues allKeys]containsObject:rowAsNum]){
            textField.text = [tempValues objectForKey:rowAsNum];
        }else {
            textField.text = self.president.toYear;
        }
        break;
    case kPartyRowIndex:
        if([[tempValues allKeys]containsObject:rowAsNum]){
            textField.text = [tempValues objectForKey:rowAsNum];
        }else {
            textField.text = self.president.party;
        }
        break;
        default:
        break;
}
if(textFieldBeingEdited == textField){
    textFieldBeingEdited = nil;
}

textField.tag = indexPath.row;
return cell;

}

// 不让选择
-(NSIndexPath *)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    return nil;
}

-(void)textFieldDidBeginEditing:(UITextField *)textField {
    self.textFieldBeingEdited = textField;
}


-(void)textFieldDidEndEditing:(UITextField *)textField {
    NSNumber *tagAsNum = [[[NSNumber alloc]initWithInt:textField.tag]autorelease];
    [tempValues setObject:textField.text forKey:tagAsNum];
}

@end
