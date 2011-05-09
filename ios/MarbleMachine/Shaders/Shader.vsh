//
//  Shader.vsh
//  MarbleMachine
//
//  Created by Nathan Swenson on 5/9/11.
//  Copyright Nathan Swenson 2011. All rights reserved.
//

attribute vec4 position;
attribute vec3 normal;
attribute vec2 textureCoordinate;

uniform mat4 modelView;
uniform mat4 projection;

uniform vec4 lightPosition;
uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;

varying lowp vec3 normalVarying;
varying lowp vec2 textureCoordinateVarying;
varying lowp vec4 diffuseVarying;

void main()
{
	// Apply model-view and projection matrices to vertex positions
    gl_Position = projection * modelView * position;
	
	// Apply normal matrix to normal
	normalVarying = vec3(normalize(modelView * vec4(normal, 0.0)));
	
	// Pass texture coordinates along
	textureCoordinateVarying = textureCoordinate;
	
	// Calculate lighting values
	vec4 lightVector = normalize(lightPosition - gl_Position);
	float lightIncidence = dot(lightVector, vec4(normalVarying, 1.0));
	diffuseVarying = lightDiffuse * vec4(max(lightIncidence, 0.0));
}
