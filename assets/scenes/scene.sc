{
	"name": "MyScene",
	"objects": [
		{
			"name": "Object_0",
			"position": {
				"x": 2,
				"y": 2,
				"z": 2
			},
			"rotation": {
				"x": 0,
				"y": 0,
				"z": 0,
				"w": 1
			},
			"scale": {
				"x": 0.75,
				"y": 0.75,
				"z": 0.75
			},
			"components": [
				{
					"type": "MeshComponent",
					"material": "materials/brick.mat",
					"mesh": {
						"type": "box",
						"x": 2,
						"y": 1,
						"z": 5
					}
				}
			]
		},
		{
			"name": "MainPlayer",
			"type": "Player",
			"position": {
				"x": 0,
				"y": 2,
				"z": 7
			},
			"components": [
				{ "type": "CameraComponent" },
				{ "type": "PlayerControllerComponent" },
				{ "type": "AudioListenerComponent" },
				{
					"type": "AudioComponent",
          "audio": [
						{
							"name": "shoot",
							"path": "audio/shoot.wav"
						},
						{
							"name": "step",
							"path": "audio/step.wav"
						},
						{
							"name": "jump",
							"path": "audio/jump.wav"
						}
          ]
				}
			],
			"children": [
				{
					"name": "Gun",
					"type": "gltf",
					"path": "models/sten_gunmachine_carbine/scene.gltf",
					"position": {
						"x": 0.75,
						"y": -0.5,
						"z": -0.75
					},
					"scale": {
						"x": -1,
						"y": 1,
						"z": 1
					}
				}
			]
		},
		{
			"name": "Ground",
			"position": {
				"x": 0,
				"y": 0,
				"z": 0
			},
			"components": [
				{
					"type": "MeshComponent",
					"mesh": {
						"type": "box",
						"x": 20,
						"y": 2,
						"z": 20
					},
					"material": "materials/brick.mat"
				},
				{
					"type": "PhysicsComponent",
					"collider": {
						"type": "box",
						"x": 20,
						"y": 2,
						"z": 20
					},
					"body": {
						"mass": 0,
						"friction": 0.5,
						"type": "static"
					}
				}
			]
		},
		{
			"name": "ObjectCollide",
			"position": {
				"x": 0,
				"y": 7,
				"z": 0
			},
			"rotation": {
				"x": 1,
				"y": 2,
				"z": 0,
				"w": 1
			},
			"components": [
				{
					"type": "MeshComponent",
					"material": "materials/brick.mat",
					"mesh": {
						"type": "box",
						"x": 1,
						"y": 1,
						"z": 1
					}
				},
				{
					"type": "PhysicsComponent",
					"collider": {
						"type": "box",
						"x": 1,
						"y": 1,
						"z": 1
					},
					"body": {
						"mass": 5,
						"friction": 0.5,
						"type": "dynamic"
					}
				}
			]
		},
		{
			"name": "Light",
			"position": {
				"x": 0,
				"y": 5,
				"z": 0
			},
			"components": [
				{
					"type": "LightComponent",
					"color": {
						"r": 1,
						"g": 1,
						"b": 1
					}
				}
			]
		}
	],
	"camera": "MainPlayer"
}
