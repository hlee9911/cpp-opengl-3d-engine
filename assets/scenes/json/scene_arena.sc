{
  "name": "MyScene",
  "objects": [
    {
      "name": "3DRoot",
      "children": [
        {
          "name": "MainPlayer",
          "type": "Player",
          "isActive": 1,
          "position": {
            "x": 4,
            "y": 2,
            "z": 12
          },
          "components": [
            {
              "type": "CameraComponent"
            },
            {
              "type": "PlayerControllerComponent"
            },
            {
              "type": "AudioListenerComponent"
            },
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
              "isActive": 1,
              "position": {
                "x": 0.75,
                "y": -0.5,
                "z": -0.75
              },
              "scale": {
                "x": -1.0,
                "y": 1.0,
                "z": 1.0
              }
            }
          ]
        },
        {
          "name": "Ground",
          "isActive": 1,
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
                "x": 60,
                "y": 1,
                "z": 60
              },
              "material": {
                "path": "materials/floor.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 1.0,
                      "value1": 1.0,
                      "value2": 1.0
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 60,
                "y": 1,
                "z": 60
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
          "name": "LeftWall",
          "isActive": 1,
          "position": {
            "x": -30.5,
            "y": 7.5,
            "z": 0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 1,
                "y": 15,
                "z": 62
              },
              "material": {
                "path": "materials/brick.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 1.0,
                      "value1": 1.0,
                      "value2": 1.0
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 1,
                "y": 15,
                "z": 62
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
          "name": "RightWall",
          "isActive": 1,
          "position": {
            "x": 30.5,
            "y": 7.5,
            "z": 0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 1,
                "y": 15,
                "z": 62
              },
              "material": {
                "path": "materials/brick.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 1.0,
                      "value1": 1.0,
                      "value2": 1.0
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 1,
                "y": 15,
                "z": 62
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
          "name": "FrontWall",
          "isActive": 1,
          "position": {
            "x": 0,
            "y": 7.5,
            "z": -30.5
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 62,
                "y": 15,
                "z": 1
              },
              "material": {
                "path": "materials/brick.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 1.0,
                      "value1": 1.0,
                      "value2": 1.0
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 62,
                "y": 15,
                "z": 1
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
          "name": "BackWall",
          "isActive": 1,
          "position": {
            "x": 0,
            "y": 7.5,
            "z": 30.5
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 62,
                "y": 15,
                "z": 1
              },
              "material": {
                "path": "materials/brick.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 1.0,
                      "value1": 1.0,
                      "value2": 1.0
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 62,
                "y": 15,
                "z": 1
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
          "name": "JumpPlatform",
          "type": "JumpPlatform",
          "isActive": 1,
          "position": {
            "x": 0,
            "y": 0.55,
            "z": 0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.1,
                "z": 4.0
              },
              "material": {
                "path": "materials/checker.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 1.0,
                      "value1": 0.0,
                      "value2": 0.0
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.1,
                "z": 4.0
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
          "name": "TowerBase",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 1.3,
            "z": -19.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 12.0,
                "y": 1.6,
                "z": 12.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 12.0,
                "y": 1.6,
                "z": 12.0
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
          "name": "TowerLowerShaft",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 3.7,
            "z": -19.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 9.0,
                "y": 3.2,
                "z": 9.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 9.0,
                "y": 3.2,
                "z": 9.0
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
          "name": "TowerUpperShaft",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 6.5,
            "z": -19.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 7.0,
                "y": 2.4,
                "z": 7.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 7.0,
                "y": 2.4,
                "z": 7.0
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
          "name": "TowerRoof",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 8.0,
            "z": -19.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 10.0,
                "y": 0.6,
                "z": 10.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 10.0,
                "y": 0.6,
                "z": 10.0
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
          "name": "TowerParapetNorth",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 8.8,
            "z": -23.8
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 10.4,
                "y": 1.0,
                "z": 0.4
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 10.4,
                "y": 1.0,
                "z": 0.4
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
          "name": "TowerParapetEast",
          "isActive": 1,
          "position": {
            "x": -14.2,
            "y": 8.8,
            "z": -19.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.4,
                "y": 1.0,
                "z": 10.4
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.4,
                "y": 1.0,
                "z": 10.4
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
          "name": "TowerParapetWest",
          "isActive": 1,
          "position": {
            "x": -23.8,
            "y": 8.8,
            "z": -19.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.4,
                "y": 1.0,
                "z": 10.4
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.4,
                "y": 1.0,
                "z": 10.4
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
          "name": "TowerParapetSouthEast",
          "isActive": 1,
          "position": {
            "x": -15.5,
            "y": 8.8,
            "z": -14.2
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.0,
                "y": 1.0,
                "z": 0.4
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.0,
                "y": 1.0,
                "z": 0.4
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
          "name": "TowerParapetSouthWest",
          "isActive": 1,
          "position": {
            "x": -22.5,
            "y": 8.8,
            "z": -14.2
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.0,
                "y": 1.0,
                "z": 0.4
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.0,
                "y": 1.0,
                "z": 0.4
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
          "name": "TowerStair_1",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 0.809,
            "z": -3.6
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_2",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 1.268,
            "z": -4.25
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_3",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 1.726,
            "z": -4.9
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_4",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 2.185,
            "z": -5.55
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_5",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 2.644,
            "z": -6.2
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_6",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 3.103,
            "z": -6.85
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_7",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 3.562,
            "z": -7.5
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_8",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 4.021,
            "z": -8.15
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_9",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 4.479,
            "z": -8.8
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_10",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 4.938,
            "z": -9.45
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_11",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 5.397,
            "z": -10.1
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_12",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 5.856,
            "z": -10.75
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_13",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 6.315,
            "z": -11.4
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_14",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 6.774,
            "z": -12.05
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_15",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 7.232,
            "z": -12.7
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_16",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 7.691,
            "z": -13.35
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "TowerStair_17",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 8.15,
            "z": -14.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "BridgeTowerWestBase",
          "isActive": 1,
          "position": {
            "x": 7.0,
            "y": 1.1,
            "z": -20.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 7.0,
                "y": 1.2,
                "z": 7.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 7.0,
                "y": 1.2,
                "z": 7.0
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
          "name": "BridgeTowerWestShaft",
          "isActive": 1,
          "position": {
            "x": 7.0,
            "y": 3.0,
            "z": -20.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 5.0,
                "y": 2.6,
                "z": 5.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 5.0,
                "y": 2.6,
                "z": 5.0
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
          "name": "BridgeTowerWestRoof",
          "isActive": 1,
          "position": {
            "x": 7.0,
            "y": 4.6,
            "z": -20.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 6.0,
                "y": 0.6,
                "z": 6.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 6.0,
                "y": 0.6,
                "z": 6.0
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
          "name": "BridgeTowerEastBase",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 1.1,
            "z": -20.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 7.0,
                "y": 1.2,
                "z": 7.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 7.0,
                "y": 1.2,
                "z": 7.0
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
          "name": "BridgeTowerEastShaft",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 3.0,
            "z": -20.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 5.0,
                "y": 2.6,
                "z": 5.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 5.0,
                "y": 2.6,
                "z": 5.0
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
          "name": "BridgeTowerEastRoof",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 4.6,
            "z": -20.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 6.0,
                "y": 0.6,
                "z": 6.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 6.0,
                "y": 0.6,
                "z": 6.0
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
          "name": "BridgeWestStair_1",
          "isActive": 1,
          "position": {
            "x": 7.0,
            "y": 0.79,
            "z": -11.6
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeWestStair_2",
          "isActive": 1,
          "position": {
            "x": 7.0,
            "y": 1.23,
            "z": -12.2
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeWestStair_3",
          "isActive": 1,
          "position": {
            "x": 7.0,
            "y": 1.67,
            "z": -12.8
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeWestStair_4",
          "isActive": 1,
          "position": {
            "x": 7.0,
            "y": 2.11,
            "z": -13.4
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeWestStair_5",
          "isActive": 1,
          "position": {
            "x": 7.0,
            "y": 2.55,
            "z": -14.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeWestStair_6",
          "isActive": 1,
          "position": {
            "x": 7.0,
            "y": 2.99,
            "z": -14.6
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeWestStair_7",
          "isActive": 1,
          "position": {
            "x": 7.0,
            "y": 3.43,
            "z": -15.2
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeWestStair_8",
          "isActive": 1,
          "position": {
            "x": 7.0,
            "y": 3.87,
            "z": -15.8
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeWestStair_9",
          "isActive": 1,
          "position": {
            "x": 7.0,
            "y": 4.31,
            "z": -16.4
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeWestStair_10",
          "isActive": 1,
          "position": {
            "x": 7.0,
            "y": 4.75,
            "z": -17.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeEastStair_1",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 0.79,
            "z": -11.6
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeEastStair_2",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 1.23,
            "z": -12.2
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeEastStair_3",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 1.67,
            "z": -12.8
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeEastStair_4",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 2.11,
            "z": -13.4
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeEastStair_5",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 2.55,
            "z": -14.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeEastStair_6",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 2.99,
            "z": -14.6
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeEastStair_7",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 3.43,
            "z": -15.2
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeEastStair_8",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 3.87,
            "z": -15.8
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeEastStair_9",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 4.31,
            "z": -16.4
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeEastStair_10",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 4.75,
            "z": -17.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.5,
                "y": 0.3,
                "z": 0.64
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
          "name": "BridgeDeck",
          "isActive": 1,
          "position": {
            "x": 15.0,
            "y": 4.5,
            "z": -20.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 10.4,
                "y": 0.8,
                "z": 6.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 10.4,
                "y": 0.8,
                "z": 6.0
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
          "name": "BridgeRailNorth",
          "isActive": 1,
          "position": {
            "x": 15.0,
            "y": 5.4,
            "z": -23.15
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 10.4,
                "y": 1.0,
                "z": 0.3
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 10.4,
                "y": 1.0,
                "z": 0.3
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
          "name": "BridgeRailSouth",
          "isActive": 1,
          "position": {
            "x": 15.0,
            "y": 5.4,
            "z": -16.85
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 10.4,
                "y": 1.0,
                "z": 0.3
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 10.4,
                "y": 1.0,
                "z": 0.3
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
          "name": "BridgeSupport_1",
          "isActive": 1,
          "position": {
            "x": 13.0,
            "y": 2.3,
            "z": -20.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.8,
                "y": 3.6,
                "z": 0.8
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.8,
                "y": 3.6,
                "z": 0.8
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
          "name": "BridgeSupport_2",
          "isActive": 1,
          "position": {
            "x": 17.0,
            "y": 2.3,
            "z": -20.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.8,
                "y": 3.6,
                "z": 0.8
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.8,
                "y": 3.6,
                "z": 0.8
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
          "name": "HubLowerPlatform",
          "isActive": 1,
          "position": {
            "x": 18.0,
            "y": 1.5,
            "z": 18.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 16.0,
                "y": 2.0,
                "z": 11.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 16.0,
                "y": 2.0,
                "z": 11.0
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
          "name": "HubUpperPlatform",
          "isActive": 1,
          "position": {
            "x": 23.0,
            "y": 5.0,
            "z": 17.5
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 5.0,
                "y": 2.0,
                "z": 10.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 5.0,
                "y": 1.0,
                "z": 10.0
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
          "name": "HubColumn_1",
          "isActive": 1,
          "position": {
            "x": 21.1,
            "y": 3.25,
            "z": 13.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.6,
                "y": 1.5,
                "z": 0.6
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.6,
                "y": 1.5,
                "z": 0.6
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
          "name": "HubColumn_2",
          "isActive": 1,
          "position": {
            "x": 24.9,
            "y": 3.25,
            "z": 13.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.6,
                "y": 1.5,
                "z": 0.6
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.6,
                "y": 1.5,
                "z": 0.6
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
          "name": "HubColumn_3",
          "isActive": 1,
          "position": {
            "x": 21.1,
            "y": 3.25,
            "z": 22.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.6,
                "y": 1.5,
                "z": 0.6
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.6,
                "y": 1.5,
                "z": 0.6
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
          "name": "HubColumn_4",
          "isActive": 1,
          "position": {
            "x": 24.9,
            "y": 3.25,
            "z": 22.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.6,
                "y": 1.5,
                "z": 0.6
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.6,
                "y": 1.5,
                "z": 0.6
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
          "name": "HubStairLower_1",
          "isActive": 1,
          "position": {
            "x": 14.0,
            "y": 0.75,
            "z": 26.1
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "HubStairLower_2",
          "isActive": 1,
          "position": {
            "x": 14.0,
            "y": 1.15,
            "z": 25.45
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "HubStairLower_3",
          "isActive": 1,
          "position": {
            "x": 14.0,
            "y": 1.55,
            "z": 24.8
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "HubStairLower_4",
          "isActive": 1,
          "position": {
            "x": 14.0,
            "y": 1.95,
            "z": 24.15
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "HubStairLower_5",
          "isActive": 1,
          "position": {
            "x": 14.0,
            "y": 2.35,
            "z": 23.5
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 4.0,
                "y": 0.3,
                "z": 0.69
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
          "name": "HubStairUpper_1",
          "isActive": 1,
          "position": {
            "x": 17.35,
            "y": 2.788,
            "z": 18.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
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
          "name": "HubStairUpper_2",
          "isActive": 1,
          "position": {
            "x": 17.8,
            "y": 3.225,
            "z": 18.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
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
          "name": "HubStairUpper_3",
          "isActive": 1,
          "position": {
            "x": 18.25,
            "y": 3.663,
            "z": 18.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
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
          "name": "HubStairUpper_4",
          "isActive": 1,
          "position": {
            "x": 18.7,
            "y": 4.1,
            "z": 18.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
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
          "name": "HubStairUpper_5",
          "isActive": 1,
          "position": {
            "x": 19.15,
            "y": 4.537,
            "z": 18.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
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
          "name": "HubStairUpper_6",
          "isActive": 1,
          "position": {
            "x": 19.6,
            "y": 4.975,
            "z": 18.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
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
          "name": "HubStairUpper_7",
          "isActive": 1,
          "position": {
            "x": 20.05,
            "y": 5.412,
            "z": 18.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
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
          "name": "HubStairUpper_8",
          "isActive": 1,
          "position": {
            "x": 20.5,
            "y": 5.85,
            "z": 18.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 0.49,
                "y": 0.3,
                "z": 2.5
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
          "name": "YardPedestalA",
          "isActive": 1,
          "position": {
            "x": -22.0,
            "y": 1.0,
            "z": 10.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 3.0,
                "y": 0.8,
                "z": 3.0
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 3.0,
                "y": 0.8,
                "z": 3.0
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
          "name": "YardPedestalB",
          "isActive": 1,
          "position": {
            "x": -10.0,
            "y": 0.8,
            "z": 22.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 2.5,
                "y": 0.6,
                "z": 2.5
              },
              "material": {
                "path": "materials/textile.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.5,
                      "value1": 0.5,
                      "value2": 0.5
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 2.5,
                "y": 0.6,
                "z": 2.5
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
          "name": "YardBox_Blue",
          "isActive": 1,
          "position": {
            "x": -24.0,
            "y": 1.6,
            "z": 9.0
          },
          "scale": {
            "x": 2.2,
            "y": 2.2,
            "z": 2.2
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 1.0,
                "y": 1.0,
                "z": 1.0
              },
              "material": {
                "path": "materials/checker.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.15,
                      "value1": 0.4,
                      "value2": 1.0
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 1.0,
                "y": 1.0,
                "z": 1.0
              },
              "body": {
                "mass": 18,
                "friction": 0.5,
                "type": "dynamic"
              }
            }
          ]
        },
        {
          "name": "YardSphere_Green",
          "isActive": 1,
          "position": {
            "x": -16.0,
            "y": 1.3,
            "z": 8.0
          },
          "scale": {
            "x": 1.6,
            "y": 1.6,
            "z": 1.6
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "sphere",
                "r": 1.0
              },
              "material": {
                "path": "materials/checker.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.2,
                      "value1": 0.85,
                      "value2": 0.25
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "sphere",
                "r": 1.0
              },
              "body": {
                "mass": 6,
                "friction": 0.5,
                "type": "dynamic"
              }
            }
          ]
        },
        {
          "name": "YardCylinder_Black",
          "isActive": 1,
          "position": {
            "x": -8.0,
            "y": 1.6,
            "z": 10.0
          },
          "scale": {
            "x": 1.6,
            "y": 2.2,
            "z": 1.6
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "cylinder",
                "r": 1.0,
                "h": 1.0
              },
              "material": {
                "path": "materials/checker.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.15,
                      "value1": 0.15,
                      "value2": 0.15
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "cylinder",
                "r": 1.0,
                "h": 1.0
              },
              "body": {
                "mass": 16,
                "friction": 0.5,
                "type": "dynamic"
              }
            }
          ]
        },
        {
          "name": "YardCone_Yellow",
          "isActive": 1,
          "position": {
            "x": -26.0,
            "y": 1.5,
            "z": 18.0
          },
          "scale": {
            "x": 1.8,
            "y": 2.0,
            "z": 1.8
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "cone",
                "r": 1.0,
                "h": 1.0
              },
              "material": {
                "path": "materials/checker.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 1.0,
                      "value1": 0.85,
                      "value2": 0.1
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "cone",
                "r": 1.0,
                "h": 1.0
              },
              "body": {
                "mass": 10,
                "friction": 0.5,
                "type": "dynamic"
              }
            }
          ]
        },
        {
          "name": "YardBox_Orange",
          "isActive": 1,
          "position": {
            "x": -22.0,
            "y": 2.0,
            "z": 18.5
          },
          "scale": {
            "x": 3.0,
            "y": 3.0,
            "z": 3.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 1.0,
                "y": 1.0,
                "z": 1.0
              },
              "material": {
                "path": "materials/checker.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 1.0,
                      "value1": 0.5,
                      "value2": 0.05
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 1.0,
                "y": 1.0,
                "z": 1.0
              },
              "body": {
                "mass": 28,
                "friction": 0.5,
                "type": "dynamic"
              }
            }
          ]
        },
        {
          "name": "YardSphere_Purple",
          "isActive": 1,
          "position": {
            "x": -13.0,
            "y": 1.05,
            "z": 24.0
          },
          "scale": {
            "x": 1.1,
            "y": 1.1,
            "z": 1.1
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "sphere",
                "r": 1.0
              },
              "material": {
                "path": "materials/checker.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.55,
                      "value1": 0.15,
                      "value2": 0.8
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "sphere",
                "r": 1.0
              },
              "body": {
                "mass": 4,
                "friction": 0.5,
                "type": "dynamic"
              }
            }
          ]
        },
        {
          "name": "YardCylinder_Blue",
          "isActive": 1,
          "position": {
            "x": -19.0,
            "y": 2.2,
            "z": 26.0
          },
          "scale": {
            "x": 1.6,
            "y": 3.4,
            "z": 1.6
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "cylinder",
                "r": 1.0,
                "h": 1.0
              },
              "material": {
                "path": "materials/checker.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.15,
                      "value1": 0.4,
                      "value2": 1.0
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "cylinder",
                "r": 1.0,
                "h": 1.0
              },
              "body": {
                "mass": 22,
                "friction": 0.5,
                "type": "dynamic"
              }
            }
          ]
        },
        {
          "name": "YardCone_Green",
          "isActive": 1,
          "position": {
            "x": -9.0,
            "y": 1.5,
            "z": 26.0
          },
          "scale": {
            "x": 2.0,
            "y": 2.0,
            "z": 2.0
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "cone",
                "r": 1.0,
                "h": 1.0
              },
              "material": {
                "path": "materials/checker.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.2,
                      "value1": 0.85,
                      "value2": 0.25
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "cone",
                "r": 1.0,
                "h": 1.0
              },
              "body": {
                "mass": 14,
                "friction": 0.5,
                "type": "dynamic"
              }
            }
          ]
        },
        {
          "name": "YardBox_Black",
          "isActive": 1,
          "position": {
            "x": -7.0,
            "y": 1.15,
            "z": 17.0
          },
          "scale": {
            "x": 1.3,
            "y": 1.3,
            "z": 1.3
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "box",
                "x": 1.0,
                "y": 1.0,
                "z": 1.0
              },
              "material": {
                "path": "materials/checker.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 0.15,
                      "value1": 0.15,
                      "value2": 0.15
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "box",
                "x": 1.0,
                "y": 1.0,
                "z": 1.0
              },
              "body": {
                "mass": 9,
                "friction": 0.5,
                "type": "dynamic"
              }
            }
          ]
        },
        {
          "name": "YardSphere_Orange",
          "isActive": 1,
          "position": {
            "x": -26.0,
            "y": 1.2,
            "z": 24.0
          },
          "scale": {
            "x": 1.4,
            "y": 1.4,
            "z": 1.4
          },
          "components": [
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "sphere",
                "r": 1.0
              },
              "material": {
                "path": "materials/checker.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 1.0,
                      "value1": 0.5,
                      "value2": 0.05
                    }
                  ]
                }
              }
            },
            {
              "type": "PhysicsComponent",
              "collider": {
                "type": "sphere",
                "r": 1.0
              },
              "body": {
                "mass": 7,
                "friction": 0.5,
                "type": "dynamic"
              }
            }
          ]
        },
        {
          "name": "Light Source",
          "isActive": 1,
          "position": {
            "x": -2,
            "y": 20,
            "z": 2
          },
          "components": [
            {
              "type": "LightComponent",
              "color": {
                "r": 1,
                "g": 1,
                "b": 1
              }
            },
            {
              "type": "MeshComponent",
              "mesh": {
                "type": "sphere",
                "r": 1
              },
              "material": {
                "path": "materials/white.mat",
                "params": {
                  "float3": [
                    {
                      "name": "color",
                      "value0": 1.0,
                      "value1": 0.95,
                      "value2": 0.8
                    }
                  ]
                }
              }
            }
          ]
        }
      ]
    },
    {
      "name": "MainCanvas",
      "isActive": 1,
      "components": [
        {
          "type": "CanvasComponent"
        },
        {
          "type": "RectTransformComponent",
          "anchor": {
            "x": 0.5,
            "y": 0.5
          },
          "pivot": {
            "x": 0,
            "y": 0
          }
        }
      ],
      "children": [
        {
          "name": "PlayButton",
          "isActive": 1,
          "position": {
            "x": 0,
            "y": 50,
            "z": 0
          },
          "components": [
            {
              "type": "ButtonComponent"
            },
            {
              "type": "RectTransformComponent",
              "anchor": {
                "x": 0.5,
                "y": 0.5
              },
              "pivot": {
                "x": 0.5,
                "y": 0.5
              },
              "size": {
                "x": 150,
                "y": 50
              }
            }
          ],
          "children": [
            {
              "name": "Text",
              "components": [
                {
                  "type": "TextComponent",
                  "text": "Start",
                  "font": {
                    "path": "fonts/arial.ttf",
                    "size": 24
                  },
                  "color": {
                    "r": 0,
                    "g": 0,
                    "b": 0,
                    "a": 1
                  }
                },
                {
                  "type": "RectTransformComponent",
                  "anchor": {
                    "x": 0.5,
                    "y": 0.5
                  },
                  "pivot": {
                    "x": 0.5,
                    "y": 0.5
                  }
                }
              ]
            }
          ]
        },
        {
          "name": "QuitButton",
          "isActive": 1,
          "position": {
            "x": 0,
            "y": -50,
            "z": 0
          },
          "components": [
            {
              "type": "ButtonComponent"
            },
            {
              "type": "RectTransformComponent",
              "anchor": {
                "x": 0.5,
                "y": 0.5
              },
              "pivot": {
                "x": 0.5,
                "y": 0.5
              },
              "size": {
                "x": 150,
                "y": 50
              }
            }
          ],
          "children": [
            {
              "name": "Text",
              "components": [
                {
                  "type": "TextComponent",
                  "text": "Quit",
                  "font": {
                    "path": "fonts/arial.ttf",
                    "size": 24
                  },
                  "color": {
                    "r": 0,
                    "g": 0,
                    "b": 0,
                    "a": 1
                  }
                },
                {
                  "type": "RectTransformComponent",
                  "anchor": {
                    "x": 0.5,
                    "y": 0.5
                  },
                  "pivot": {
                    "x": 0.5,
                    "y": 0.5
                  }
                }
              ]
            }
          ]
        }
      ]
    }
  ],
  "camera": "MainPlayer",
  "activeCanvas": "MainCanvas"
}
