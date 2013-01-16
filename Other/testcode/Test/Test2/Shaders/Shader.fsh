//
//  Shader.fsh
//  Test2
//
//  Created by 佳 刘 on 12-7-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
