//
//  Shader.fsh
//  MarbleMachine
//
//  Created by Nathan Swenson on 5/9/11.
//  Copyright Nathan Swenson 2011. All rights reserved.
//

uniform lowp vec4 lightAmbient;
uniform sampler2D textureNumber;

varying lowp vec3 normalVarying;
varying lowp vec2 textureCoordinateVarying;
varying lowp vec4 diffuseVarying;

void main()
{
	lowp vec4 textureColor = texture2D(textureNumber, textureCoordinateVarying);
    gl_FragColor = textureColor * (lightAmbient + diffuseVarying);
}
