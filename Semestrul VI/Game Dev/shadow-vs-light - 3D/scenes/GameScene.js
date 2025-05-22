import * as THREE from 'three';
import Ammo from 'ammojs-typed'

export default class GameScene {
    constructor(container, user1 = 'Jucător A', user2 = 'Jucător B') {
        this.container = container;
        this.user1 = user1;
        this.user2 = user2;

        this.scene = new THREE.Scene();
        this.camera = new THREE.PerspectiveCamera(55, container.clientWidth / container.clientHeight, 0.1, 1000);
        this.renderer = new THREE.WebGLRenderer({antialias: true, alpha: true});

        this.clock = new THREE.Clock();
        this.mixers = [];
        this.players = {};

        // Physics world
        this.physicsWorld = null;
        this.rigidBodies = [];
        this.physicsEnabled = true;
        this.tmpTransform = null;

        this.keys = {};
        this.roundHealth = {A: [100, 100, 100], B: [100, 100, 100]};
        this.currentHealth = {A: 100, B: 100};
        this.rounds = {A: 0, B: 0};
        this.roundOngoing = true;
        this.roundTransition = false;
        this.lastPunch = {A: 0, B: 0};
        this.currentRound = 1;

        this.ATTACK_RANGE = 2.5;
        this.ARENA_LIMIT = 5.5;
        this.PUNCH_DURATION = 0.35;
        this.PUNCH_COOLDOWN = 0.8;
        this.PUNCH_DAMAGE = 15;
        this.KNOCKBACK = 0.4;
        this.RING_RADIUS = 5.2;
        this.GRAVITY = -9.82;
        this.MOVE_SPEED = 6;

        this.ui = {labels: {}, bars: {}, score: null, round: null};
        this.hitEffects = [];
        this.animationStates = {A: 'idle', B: 'idle'};
        this.punchAnimations = {A: 0, B: 0};
        this.Ammo = null;
    }

    async init() {
        // Initialize Ammo.js physics
        await this.initPhysics();

        const DPR_LIMIT = 1.5;
        this.renderer.setPixelRatio(Math.min(window.devicePixelRatio, DPR_LIMIT));
        this.renderer.outputColorSpace = THREE.SRGBColorSpace;   // implicit din r150+
        this.renderer.setSize(this.container.clientWidth, this.container.clientHeight);
        this.renderer.shadowMap.enabled = true;
        this.renderer.shadowMap.type = THREE.PCFSoftShadowMap;
        this.renderer.setClearColor(0x1e3a8a);
        this.container.appendChild(this.renderer.domElement);

        // Resize handler
        window.addEventListener('resize', () => {
            this.camera.aspect = this.container.clientWidth / this.container.clientHeight;
            this.camera.updateProjectionMatrix();
            this.renderer.setSize(this.container.clientWidth, this.container.clientHeight);
        });

        // Setup scene
        const sky = new THREE.Color(0x1e3a8a);
        const hor = new THREE.Color(0x3b82f6);
        this.scene.background = sky;
        this.scene.fog = new THREE.Fog(hor, 15, 30);

        // Enhanced lighting system
        this.setupLighting();

        this.buildEnvironment();
        this.camera.position.set(0, 8, 14);
        this.camera.lookAt(0, 1.5, 0);

        this.createCharacter(-3, 'A', this.user1, 0x2196f3);
        this.createCharacter(3, 'B', this.user2, 0xf44336);

        this.createGameUI();
        this.setupControls();
        this.updateRoundDisplay();
        this.animate();
        this.showRoundTransition(`Runda ${this.currentRound}`);
    }

    async initPhysics() {
        try {
            // Initialize Ammo.js - this returns a promise that resolves to the Ammo module
            this.Ammo = await Ammo();

            // Set up global reference for backward compatibility
            if (typeof window !== 'undefined') {
                window.Ammo = this.Ammo;
            }

            // Initialize physics world
            const collisionConfiguration = new this.Ammo.btDefaultCollisionConfiguration();
            const dispatcher = new this.Ammo.btCollisionDispatcher(collisionConfiguration);
            const overlappingPairCache = new this.Ammo.btDbvtBroadphase();
            const solver = new this.Ammo.btSequentialImpulseConstraintSolver();

            this.physicsWorld = new this.Ammo.btDiscreteDynamicsWorld(
                dispatcher,
                overlappingPairCache,
                solver,
                collisionConfiguration
            );

            this.physicsWorld.setGravity(new this.Ammo.btVector3(0, this.GRAVITY, 0));
            this.physicsWorld.getSolverInfo().m_minimumSolverBatchSize = 128; // Reduce overhead
            this.physicsWorld.getDispatchInfo().m_allowedCcdPenetration = 0.0001; // Reduce precizie

            console.log('Physics initialized successfully');
        } catch (error) {
            console.error('Failed to initialize physics:', error);
            this.physicsEnabled = false;
        }


    }

    setupLighting() {
        // Enhanced hemisphere light
        const hemi = new THREE.HemisphereLight(0xffffff, 0x444444, 0.8);
        hemi.position.set(0, 20, 0);
        this.scene.add(hemi);

        // Main directional light with dynamic shadows
        const dir = new THREE.DirectionalLight(0xffffff, 1.2);
        dir.position.set(6, 12, 8);
        dir.castShadow = true;
        // În setupLighting(), ajustează dimensiunile shadow map
        dir.shadow.mapSize.set(1024, 1024); // Redus de la 2048
        dir.shadow.camera.left = dir.shadow.camera.bottom = -15;
        dir.shadow.camera.right = dir.shadow.camera.top = 15;
        dir.shadow.camera.near = 0.1;
        dir.shadow.camera.far = 50;
        dir.shadow.bias = -0.0001;
        this.scene.add(dir);

        // Spotlight for dramatic effect
        const spot = new THREE.SpotLight(0xffffff, 1.5, 25, Math.PI / 4, 0.5, 1);
        spot.position.set(0, 15, 0);
        spot.target.position.set(0, 0, 0);
        spot.castShadow = true;
        spot.shadow.mapSize.set(512, 512);   // Redus de la 1024
        this.scene.add(spot, spot.target);

        // Ambient lighting for mood
        const ambient = new THREE.AmbientLight(0x404040, 0.3);
        this.scene.add(ambient);
    }

    buildEnvironment() {
        // Main floor with physics
        const floorGeometry = new THREE.PlaneGeometry(40, 40);
        const floorMaterial = new THREE.MeshStandardMaterial({
            color: 0x111827,
            roughness: 0.8,
            metalness: 0.1
        });
        const floor = new THREE.Mesh(floorGeometry, floorMaterial);
        floor.rotation.x = -Math.PI / 2;
        floor.position.y = -0.05;
        floor.receiveShadow = true;
        this.scene.add(floor);

        // Add physics to floor
        if (this.physicsEnabled) {
            this.createRigidBody(floor, 'box', 0, {width: 40, height: 0.1, depth: 40});
        }

        // Ring platform with enhanced materials
        const ringGeometry = new THREE.CylinderGeometry(this.RING_RADIUS, this.RING_RADIUS, 0.4, 32);
        const ringMaterial = new THREE.MeshStandardMaterial({
            color: 0x8B4513,
            roughness: 0.6,
            metalness: 0.2,
            normalMap: this.createWoodNormalMap()
        });
        const ringPlatform = new THREE.Mesh(ringGeometry, ringMaterial);
        ringPlatform.position.y = 0.2;
        ringPlatform.receiveShadow = true;
        ringPlatform.castShadow = true;
        this.scene.add(ringPlatform);

        // Add physics to ring
        if (this.physicsEnabled) {
            this.createRigidBody(ringPlatform, 'cylinder', 0, {radius: this.RING_RADIUS, height: 0.4});
        }

        // Ring posts with physics
        this.createRingPosts();

        // Ring ropes
        this.createRingRopes();

        // Enhanced ring lighting
        this.createRingLighting();
    }

    createWoodNormalMap() {
        const canvas = document.createElement('canvas');
        canvas.width = canvas.height = 256;
        const ctx = canvas.getContext('2d');

        // Create wood grain pattern
        const imageData = ctx.createImageData(256, 256);
        const data = imageData.data;

        for (let i = 0; i < data.length; i += 4) {
            const noise = Math.random() * 0.3 + 0.7;
            data[i] = 128 + (noise - 0.5) * 60;     // R
            data[i + 1] = 128 + (noise - 0.5) * 60; // G
            data[i + 2] = 255;                       // B
            data[i + 3] = 255;                       // A
        }

        ctx.putImageData(imageData, 0, 0);

        const texture = new THREE.CanvasTexture(canvas);
        texture.wrapS = texture.wrapT = THREE.RepeatWrapping;
        texture.repeat.set(4, 4);
        return texture;
    }

    createRingPosts() {
        const posts = [];
        for (let i = 0; i < 4; i++) {
            const angle = (i / 4) * Math.PI * 2;
            const x = Math.cos(angle) * (this.RING_RADIUS + 0.6);
            const z = Math.sin(angle) * (this.RING_RADIUS + 0.6);

            const postGeometry = new THREE.CylinderGeometry(0.08, 0.08, 3, 8);
            const postMaterial = new THREE.MeshStandardMaterial({
                color: 0x444444,
                roughness: 0.3,
                metalness: 0.8
            });
            const post = new THREE.Mesh(postGeometry, postMaterial);
            post.position.set(x, 1.5, z);
            post.castShadow = true;
            this.scene.add(post);
            posts.push(post);

            // Add physics to posts
            if (this.physicsEnabled) {
                this.createRigidBody(post, 'cylinder', 0, {radius: 0.08, height: 3});
            }
        }
    }

    createRingRopes() {
        for (let level = 0; level < 3; level++) {
            const y = 0.8 + level * 0.6;
            const ropeGeometry = new THREE.TorusGeometry(this.RING_RADIUS + 0.6, 0.04, 6, 32);
            const ropeMaterial = new THREE.MeshStandardMaterial({
                color: 0xff0000,
                roughness: 0.4,
                metalness: 0.1
            });
            const rope = new THREE.Mesh(ropeGeometry, ropeMaterial);
            rope.position.y = y;
            rope.rotation.x = Math.PI / 2;
            this.scene.add(rope);
        }
    }

    createRingLighting() {
        for (let i = 0; i < 4; i++) {
            const angle = (i / 4) * Math.PI * 2;
            const x = Math.cos(angle) * (this.RING_RADIUS + 2);
            const z = Math.sin(angle) * (this.RING_RADIUS + 2);

            const light = new THREE.SpotLight(0xffffff, 0.8, 15, Math.PI / 6, 0.3, 1);
            light.position.set(x, 8, z);
            light.target.position.set(0, 1, 0);
            light.castShadow = true;
            light.shadow.mapSize.set(512, 512);
            this.scene.add(light, light.target);
        }
    }

    createRigidBody(mesh, shape, mass, params = {}) {
        if (!this.physicsEnabled || !this.Ammo) return;

        let btShape;
        const pos = mesh.position;
        const quat = mesh.quaternion;

        switch (shape) {
            case 'box':
                const {width = 1, height = 1, depth = 1} = params;
                btShape = new this.Ammo.btBoxShape(new this.Ammo.btVector3(width/2, height/2, depth/2));
                break;
            case 'cylinder':
                const {radius = 1, height: cylHeight = 1} = params;
                btShape = new this.Ammo.btCylinderShape(new this.Ammo.btVector3(radius, cylHeight/2, radius));
                break;
            case 'sphere':
                const {radius: sphereRadius = 1} = params;
                btShape = new this.Ammo.btSphereShape(sphereRadius);
                break;
            default:
                btShape = new this.Ammo.btBoxShape(new this.Ammo.btVector3(0.5, 0.5, 0.5));
        }

        const transform = new this.Ammo.btTransform();
        transform.setIdentity();
        transform.setOrigin(new this.Ammo.btVector3(pos.x, pos.y, pos.z));
        transform.setRotation(new this.Ammo.btQuaternion(quat.x, quat.y, quat.z, quat.w));

        const motionState = new this.Ammo.btDefaultMotionState(transform);
        const localInertia = new this.Ammo.btVector3(0, 0, 0);

        if (mass > 0) {
            btShape.calculateLocalInertia(mass, localInertia);
        }

        const rbInfo = new this.Ammo.btRigidBodyConstructionInfo(mass, motionState, btShape, localInertia);
        const body = new this.Ammo.btRigidBody(rbInfo);

        this.physicsWorld.addRigidBody(body);

        this.rigidBodies.push({
            mesh: mesh,
            body: body
        });

        return body;
    }

    createCharacter(x, key, nick, tint) {
        const group = new THREE.Group();

        // Enhanced body with better materials
        const bodyGeometry = new THREE.CylinderGeometry(0.4, 0.35, 1.6, 8);
        const bodyMaterial = new THREE.MeshStandardMaterial({
            color: tint,
            roughness: 0.7,
            metalness: 0.1,
            emissive: new THREE.Color(tint).multiplyScalar(0.1)
        });
        const body = new THREE.Mesh(bodyGeometry, bodyMaterial);
        body.position.y = 0.8;
        body.castShadow = true;
        group.add(body);

        // Enhanced head with skin texture
        const headGeometry = new THREE.SphereGeometry(0.25, 12, 8);
        const headMaterial = new THREE.MeshStandardMaterial({
            color: 0xffdbac,
            roughness: 0.8,
            metalness: 0.0,
            subsurface: 0.3
        });
        const head = new THREE.Mesh(headGeometry, headMaterial);
        head.position.y = 1.85;
        head.castShadow = true;
        group.add(head);

        // Enhanced arms with proper proportions
        const armGeometry = new THREE.CylinderGeometry(0.08, 0.12, 0.7, 6);
        const armMaterial = new THREE.MeshStandardMaterial({
            color: 0xffdbac,
            roughness: 0.8,
            metalness: 0.0
        });

        const leftArm = new THREE.Mesh(armGeometry, armMaterial);
        leftArm.position.set(-0.45, 1.1, 0);
        leftArm.castShadow = true;
        group.add(leftArm);

        const rightArm = new THREE.Mesh(armGeometry, armMaterial);
        rightArm.position.set(0.45, 1.1, 0);
        rightArm.castShadow = true;
        group.add(rightArm);

        // Enhanced gloves with leather material
        const gloveGeometry = new THREE.SphereGeometry(0.15, 8, 6);
        const gloveMaterial = new THREE.MeshStandardMaterial({
            color: 0x8B0000,
            roughness: 0.4,
            metalness: 0.2,
            normalMap: this.createLeatherNormalMap()
        });

        const leftGlove = new THREE.Mesh(gloveGeometry, gloveMaterial);
        leftGlove.position.set(-0.45, 0.65, 0);
        leftGlove.castShadow = true;
        group.add(leftGlove);

        const rightGlove = new THREE.Mesh(gloveGeometry, gloveMaterial);
        rightGlove.position.set(0.45, 0.65, 0);
        rightGlove.castShadow = true;
        group.add(rightGlove);

        // Enhanced legs
        const legGeometry = new THREE.CylinderGeometry(0.12, 0.1, 0.8, 6);
        const legMaterial = new THREE.MeshStandardMaterial({
            color: tint,
            roughness: 0.7,
            metalness: 0.1
        });

        const leftLeg = new THREE.Mesh(legGeometry, legMaterial);
        leftLeg.position.set(-0.15, 0, 0);
        leftLeg.castShadow = true;
        group.add(leftLeg);

        const rightLeg = new THREE.Mesh(legGeometry, legMaterial);
        rightLeg.position.set(0.15, 0, 0);
        rightLeg.castShadow = true;
        group.add(rightLeg);

        // Initial positioning
        const initialPosition = new THREE.Vector3(x, 0.4, 0);
        const initialRotation = key === 'A' ? Math.PI / 2 : -Math.PI / 2;

        group.position.copy(initialPosition);
        group.rotation.y = initialRotation;
        this.scene.add(group);

        // Create physics body for character
        let physicsBody = null;
        if (this.physicsEnabled) {
            physicsBody = this.createRigidBody(group, 'cylinder', 75, {radius: 0.4, height: 1.8});
            if (physicsBody) {
                physicsBody.setAngularFactor(new this.Ammo.btVector3(0, 1, 0)); // Only allow Y rotation
                physicsBody.setFriction(0.8);
                physicsBody.setRestitution(0.1);
            }
        }

        // Store player references
        this.players[key] = {
            model: group,
            body: body,
            head: head,
            leftArm: leftArm,
            rightArm: rightArm,
            leftGlove: leftGlove,
            rightGlove: rightGlove,
            leftLeg: leftLeg,
            rightLeg: rightLeg,
            tint: tint,
            nick: nick,
            dir: key === 'A' ? 1 : -1,
            velocity: new THREE.Vector3(0, 0, 0),
            knockbackVelocity: 0,
            physicsBody: physicsBody,
            originalPositions: {
                leftArm: leftArm.position.clone(),
                rightArm: rightArm.position.clone(),
                leftGlove: leftGlove.position.clone(),
                rightGlove: rightGlove.position.clone()
            }
        };

        this.initPlayerUI(key, nick, tint);
    }

    createLeatherNormalMap() {
        const canvas = document.createElement('canvas');
        canvas.width = canvas.height = 128;
        const ctx = canvas.getContext('2d');

        const imageData = ctx.createImageData(128, 128);
        const data = imageData.data;

        for (let i = 0; i < data.length; i += 4) {
            const noise = Math.random() * 0.2 + 0.8;
            data[i] = 128 + (noise - 0.5) * 40;     // R
            data[i + 1] = 128 + (noise - 0.5) * 40; // G
            data[i + 2] = 255;                       // B
            data[i + 3] = 255;                       // A
        }

        ctx.putImageData(imageData, 0, 0);

        const texture = new THREE.CanvasTexture(canvas);
        texture.wrapS = texture.wrapT = THREE.RepeatWrapping;
        return texture;
    }

    setupControls() {
        window.addEventListener('keydown', (e) => {
            this.keys[e.code] = true;
        });

        window.addEventListener('keyup', (e) => {
            this.keys[e.code] = false;
        });
    }

    updatePhysics(dt) {
        if (!this.physicsEnabled || !this.physicsWorld) return;

        this.physicsWorld.stepSimulation(dt, 10);

        // Update mesh positions from physics bodies
        this.rigidBodies.forEach(obj => {
            const ms = obj.body.getMotionState();
            if (ms) {
                ms.getWorldTransform(this.tmpTransform);
                const p = this.tmpTransform.getOrigin();
                const q = this.tmpTransform.getRotation();
                obj.mesh.position.set(p.x(), p.y(), p.z());
                obj.mesh.quaternion.set(q.x(), q.y(), q.z(), q.w());
            }
        });
    }

    handleInput(dt, t) {
        if (!this.roundOngoing || this.roundTransition) return;

        const speed = this.MOVE_SPEED;
        const A = this.players.A;
        const B = this.players.B;
        if (!A || !B) return;

        // Reset velocities
        A.velocity.set(0, 0, 0);
        B.velocity.set(0, 0, 0);

        // Player A controls (WASD)
        if (this.keys['KeyA']) A.velocity.x = -speed;
        if (this.keys['KeyD']) A.velocity.x = speed;
        if (this.keys['KeyW']) A.velocity.z = -speed;
        if (this.keys['KeyS']) A.velocity.z = speed;

        // Player B controls (Arrow keys)
        if (this.keys['ArrowLeft']) B.velocity.x = -speed;
        if (this.keys['ArrowRight']) B.velocity.x = speed;
        if (this.keys['ArrowUp']) B.velocity.z = -speed;
        if (this.keys['ArrowDown']) B.velocity.z = speed;

        // Apply movement
        this.movePlayer('A', dt);
        this.movePlayer('B', dt);

        // Update animations
        this.updateAnimations(dt, t);

        // Handle punches
        if (this.keys['Space'] && t - this.lastPunch.A > this.PUNCH_COOLDOWN) {
            this.executePunch('A', 'B', t);
        }

        if (this.keys['Enter'] && t - this.lastPunch.B > this.PUNCH_COOLDOWN) {
            this.executePunch('B', 'A', t);
        }
    }

    movePlayer(playerId, dt) {
        const player = this.players[playerId];
        if (!player) return;

        if (this.physicsEnabled && player.physicsBody && this.Ammo) {
            // Use physics for movement
            const velocity = player.velocity.clone();
            const currentVel = player.physicsBody.getLinearVelocity();

            // Apply horizontal movement, preserve vertical velocity
            player.physicsBody.setLinearVelocity(new this.Ammo.btVector3(
                velocity.x,
                currentVel.y(),
                velocity.z
            ));

            // Check ring boundaries
            const pos = player.model.position;
            const distanceFromCenter = Math.sqrt(pos.x * pos.x + pos.z * pos.z);
            if (distanceFromCenter > this.RING_RADIUS - 0.4) {
                const centerDir = new THREE.Vector3(pos.x, 0, pos.z).normalize().multiplyScalar(-50);
                player.physicsBody.setLinearVelocity(new this.Ammo.btVector3(
                    centerDir.x,
                    currentVel.y(),
                    centerDir.z
                ));
            }
        } else {
            // Fallback to manual movement
            const velocity = player.velocity.clone().multiplyScalar(dt);
            const newPos = player.model.position.clone().add(velocity);

            // Check ring limits
            const distanceFromCenter = Math.sqrt(newPos.x * newPos.x + newPos.z * newPos.z);
            if (distanceFromCenter <= this.RING_RADIUS - 0.4) {
                player.model.position.copy(newPos);
            }
        }

        // Face opponent
        const otherId = playerId === 'A' ? 'B' : 'A';
        const other = this.players[otherId];
        if (other) {
            const lookDirection = other.model.position.clone().sub(player.model.position);
            const angle = Math.atan2(lookDirection.x, lookDirection.z);
            player.model.rotation.y = angle;
        }
    }

    updateAnimations(dt, t) {
        Object.keys(this.players).forEach(playerId => {
            const player = this.players[playerId];
            const isMoving = player.velocity.length() > 0.1;
            const isPunching = t - this.lastPunch[playerId] < this.PUNCH_DURATION;

            if (isPunching) {
                this.animationStates[playerId] = 'punch';
                this.animatePunch(player, t - this.lastPunch[playerId]);
            } else if (isMoving) {
                this.animationStates[playerId] = 'walk';
                this.animateWalk(player, t);
                this.resetPunchAnimation(player);
            } else {
                this.animationStates[playerId] = 'idle';
                this.animateIdle(player, t);
                this.resetPunchAnimation(player);
            }
        });
    }

    animateIdle(player, time) {
        const breathe = Math.sin(time * 2) * 0.02;
        player.body.scale.y = 1 + breathe;

        const sway = Math.sin(time * 1.5) * 0.05;
        player.leftArm.rotation.z = sway;
        player.rightArm.rotation.z = -sway;

        // Subtle head movement
        const headBob = Math.sin(time * 1.2) * 0.02;
        player.head.position.y = 1.85 + headBob;
    }

    resetPunchAnimation(player) {
        player.rightArm.position.copy(player.originalPositions.rightArm);
        player.rightGlove.position.copy(player.originalPositions.rightGlove);
        player.body.rotation.y = 0;
        player.head.position.x = 0;
        player.leftArm.rotation.x = 0;
        player.rightArm.rotation.x = 0;
        player.leftLeg.rotation.x = 0;
        player.rightLeg.rotation.x = 0;
        player.body.scale.y = 1;
        player.leftArm.rotation.z = 0;
        player.rightArm.rotation.z = 0;
    }

    executePunch(attackerId, defenderId, time) {
        const attacker = this.players[attackerId];
        const defender = this.players[defenderId];
        if (!attacker || !defender) return;

        this.lastPunch[attackerId] = time;

        // Check distance for hit
        const distance = attacker.model.position.distanceTo(defender.model.position);
        if (distance <= this.ATTACK_RANGE) {
            setTimeout(() => {
                this.dealDamage(defenderId, attackerId);
            }, 200); // Sync with animation
        }
    }

    dealDamage(targetId, attackerId) {
        if (!this.roundOngoing) return;

        this.currentHealth[targetId] -= this.PUNCH_DAMAGE;

        // Visual hit effect
        this.createHitEffect(targetId);

        // Physics-based knockback
        const target = this.players[targetId];
        const attacker = this.players[attackerId];

        if (target && attacker) {
            const knockbackDir = target.model.position.clone().sub(attacker.model.position).normalize();

            if (this.physicsEnabled && target.physicsBody) {
                // Apply physics-based knockback
                const knockbackForce = new Ammo.btVector3(
                    knockbackDir.x * 15,
                    2, // Small upward force
                    knockbackDir.z * 15
                );
                target.physicsBody.applyCentralImpulse(knockbackForce);
            } else {
                // Fallback manual knockback
                target.model.position.add(knockbackDir.multiplyScalar(this.KNOCKBACK));

                // Keep in ring bounds
                const distFromCenter = Math.sqrt(target.model.position.x ** 2 + target.model.position.z ** 2);
                if (distFromCenter > this.RING_RADIUS - 0.4) {
                    const centerDir = target.model.position.clone().normalize().multiplyScalar(-(distFromCenter - (this.RING_RADIUS - 0.4)));
                    target.model.position.add(centerDir);
                }
            }
        }

        // Check round end
        if (this.currentHealth[targetId] <= 0) {
            this.endRound(attackerId);
        }

        this.updateHealthBars();
    }

    createHitEffect(playerId) {
        const player = this.players[playerId];
        if (!player) return;

        // Enhanced particle system for hit effect
        const particleCount = 15;
        const particles = new THREE.Group();

        for (let i = 0; i < particleCount; i++) {
            const particle = new THREE.Mesh(
                new THREE.SphereGeometry(0.05, 6, 6),
                new THREE.MeshBasicMaterial({
                    color: new THREE.Color().setHSL(0, 1, 0.5 + Math.random() * 0.5),
                    transparent: true,
                    opacity: 0.8
                })
            );

            // Random position around impact point
            const angle = (i / particleCount) * Math.PI * 2;
            const radius = Math.random() * 0.3;
            particle.position.set(
                Math.cos(angle) * radius,
                Math.random() * 0.5,
                Math.sin(angle) * radius
            );

            particles.add(particle);
        }

        particles.position.copy(player.model.position);
        particles.position.y += 1.5;
        this.scene.add(particles);

        // Animate particles
        const startTime = this.clock.elapsedTime;
        const animateParticles = () => {
            const elapsed = this.clock.elapsedTime - startTime;
            if (elapsed < 1.0) {
                particles.children.forEach((particle, index) => {
                    const speed = 2 + Math.random() * 2;
                    const direction = new THREE.Vector3(
                        (Math.random() - 0.5) * 2,
                        Math.random() + 0.5,
                        (Math.random() - 0.5) * 2
                    ).normalize();

                    particle.position.add(direction.multiplyScalar(0.02 * speed));
                    particle.material.opacity = Math.max(0, 0.8 - elapsed * 0.8);
                    particle.scale.setScalar(1 + elapsed * 2);
                });
                requestAnimationFrame(animateParticles);
            } else {
                this.scene.remove(particles);
            }
        };
        animateParticles();

        // Screen shake effect
        this.addScreenShake(0.1, 200);

        // UI damage indicator
        if (typeof document !== 'undefined') {
            const effect = document.createElement('div');
            effect.style.position = 'absolute';
            effect.style.color = '#ff4444';
            effect.style.fontWeight = 'bold';
            effect.style.fontSize = '28px';
            effect.style.pointerEvents = 'none';
            effect.style.zIndex = '100';
            effect.style.textShadow = '2px 2px 4px #000';
            effect.style.animation = 'hitEffect 1.2s ease-out forwards';
            effect.textContent = `-${this.PUNCH_DAMAGE}`;

            const rect = this.renderer.domElement.getBoundingClientRect();
            effect.style.left = (rect.width / 2 + (playerId === 'A' ? -100 : 100)) + 'px';
            effect.style.top = (rect.height / 2 - 50) + 'px';

            document.body.appendChild(effect);
            setTimeout(() => {
                if (document.body.contains(effect)) {
                    document.body.removeChild(effect);
                }
            }, 1200);
        }
    }

    addScreenShake(intensity, duration) {
        const originalPosition = this.camera.position.clone();
        const startTime = this.clock.elapsedTime;

        const shakeAnimation = () => {
            const elapsed = this.clock.elapsedTime - startTime;
            if (elapsed < duration / 1000) {
                const progress = elapsed / (duration / 1000);
                const currentIntensity = intensity * (1 - progress);

                this.camera.position.copy(originalPosition);
                this.camera.position.add(new THREE.Vector3(
                    (Math.random() - 0.5) * currentIntensity,
                    (Math.random() - 0.5) * currentIntensity,
                    (Math.random() - 0.5) * currentIntensity
                ));

                requestAnimationFrame(shakeAnimation);
            } else {
                this.camera.position.copy(originalPosition);
            }
        };
        shakeAnimation();
    }

    endRound(winnerId) {
        this.roundOngoing = false;
        this.rounds[winnerId]++;
        this.updateRoundDisplay();

        if (this.rounds[winnerId] >= 2) {
            this.endGame(winnerId);
        } else {
            this.startNextRound();
        }
    }

    startNextRound() {
        this.currentRound++;
        this.roundTransition = true;

        // Reset health
        this.currentHealth = {A: 100, B: 100};

        // Reset positions
        this.resetPlayerPositions();

        this.showRoundTransition(`Runda ${this.currentRound}`);
        this.updateHealthBars();

        this.updateRoundDisplay();
        setTimeout(() => {
            this.roundOngoing = true;
            this.roundTransition = false;
        }, 2000);
    }

    resetPlayerPositions() {
        const positions = {A: {x: -3, y: 0.4, z: 0}, B: {x: 3, y: 0.4, z: 0}};
        const rotations = {A: Math.PI / 2, B: -Math.PI / 2};

        Object.keys(this.players).forEach(key => {
            const player = this.players[key];
            const pos = positions[key];

            if (this.physicsEnabled && player.physicsBody) {
                // Reset physics body
                const transform = new Ammo.btTransform();
                transform.setIdentity();
                transform.setOrigin(new Ammo.btVector3(pos.x, pos.y + 0.8, pos.z));
                transform.setRotation(new Ammo.btQuaternion(0, Math.sin(rotations[key]/2), 0, Math.cos(rotations[key]/2)));

                player.physicsBody.setWorldTransform(transform);
                player.physicsBody.setLinearVelocity(new Ammo.btVector3(0, 0, 0));
                player.physicsBody.setAngularVelocity(new Ammo.btVector3(0, 0, 0));
            } else {
                // Manual reset
                player.model.position.set(pos.x, pos.y, pos.z);
                player.model.rotation.y = rotations[key];
            }
        });
    }

    endGame(winnerId) {
        const winner = this.players[winnerId];
        const winnerName = winner ? winner.nick : `Jucător ${winnerId}`;

        // Victory celebration effect
        this.createVictoryEffect(winnerId);
        this.showRoundTransition(`${winnerName} a câștigat!`);

        setTimeout(() => {
            // Complete reset
            this.rounds = {A: 0, B: 0};
            this.currentRound = 1;
            this.currentHealth = {A: 100, B: 100};

            this.resetPlayerPositions();
            this.updateHealthBars();

            if (this.ui.round) {
                this.updateRoundDisplay();
            }

            this.roundOngoing = true;
            this.roundTransition = false;
        }, 4000);
    }

    createVictoryEffect(winnerId) {
        const winner = this.players[winnerId];
        if (!winner) return;

        // Fireworks effect
        for (let i = 0; i < 20; i++) {
            setTimeout(() => {
                const firework = new THREE.Group();
                const particleCount = 30;

                for (let j = 0; j < particleCount; j++) {
                    const particle = new THREE.Mesh(
                        new THREE.SphereGeometry(0.05, 6, 6),
                        new THREE.MeshBasicMaterial({
                            color: new THREE.Color().setHSL(Math.random(), 1, 0.7),
                            transparent: true
                        })
                    );
                    firework.add(particle);
                }

                firework.position.set(
                    (Math.random() - 0.5) * 10,
                    5 + Math.random() * 3,
                    (Math.random() - 0.5) * 10
                );

                this.scene.add(firework);

                // Animate firework
                const startTime = this.clock.elapsedTime;
                const animateFirework = () => {
                    const elapsed = this.clock.elapsedTime - startTime;
                    if (elapsed < 2.0) {
                        firework.children.forEach((particle, index) => {
                            const angle = (index / particleCount) * Math.PI * 2;
                            const speed = 0.05 * elapsed;
                            particle.position.x += Math.cos(angle) * speed;
                            particle.position.z += Math.sin(angle) * speed;
                            particle.position.y -= 0.02;
                            particle.material.opacity = Math.max(0, 1 - elapsed * 0.5);
                        });
                        requestAnimationFrame(animateFirework);
                    } else {
                        this.scene.remove(firework);
                    }
                };
                animateFirework();
            }, i * 100);
        }
    }

    showRoundTransition(text) {
        if (typeof document === 'undefined') return;

        let indicator = document.querySelector('.round-indicator');
        if (!indicator) {
            indicator = document.createElement('div');
            indicator.className = 'round-indicator';
            indicator.style.cssText = `
                position: absolute;
                top: 50%;
                left: 50%;
                transform: translate(-50%, -50%);
                font: 900 48px Arial;
                color: #fff;
                text-shadow: 3px 3px 6px #000;
                pointer-events: none;
                opacity: 0;
                transition: opacity 0.5s;
                z-index: 20;
                background: rgba(0,0,0,0.7);
                padding: 20px 40px;
                border-radius: 15px;
                backdrop-filter: blur(10px);
            `;
            document.body.appendChild(indicator);
        }

        indicator.textContent = text;
        indicator.style.opacity = '1';

        setTimeout(() => {
            indicator.style.opacity = '0';
        }, 2000);
    }

    updateRoundDisplay() {
        if (this.ui.round) {
            this.ui.round.textContent = `Runda ${this.currentRound} - ${this.rounds.A}:${this.rounds.B}`;
        }
    }

    animate() {
        requestAnimationFrame(() => this.animate());

        const dtRaw  = this.clock.getDelta();          // secunde reale de la ultimul frame
        const dtPhys = Math.min(dtRaw, 1/30);          // max 33 ms pentru Bullet
        const t      = this.clock.elapsedTime;

        // Handle input and game logic
        this.handleInput(dtRaw, t);

        // Update camera for dynamic effects
        this.updateCamera(t);

        this.renderer.render(this.scene, this.camera);
        if (this.physicsEnabled) this.physicsWorld.stepSimulation(dtPhys, 2, 1/60);
    }

    updateCamera(time) {
        // Dynamic camera movement for more engaging viewing
        const basePosition = new THREE.Vector3(0, 8, 14);
        const sway = Math.sin(time * 0.5) * 0.3;

        this.camera.position.x = basePosition.x + sway;
        this.camera.position.y = basePosition.y + Math.sin(time * 0.3) * 0.2;
        this.camera.position.z = basePosition.z + Math.cos(time * 0.4) * 0.5;

        this.camera.lookAt(0, 1.5, 0);
    }

    initPlayerUI(key, nick, tint) {
        if (typeof document === 'undefined') return;

        const isPlayerA = key === 'A';
        const x = isPlayerA ? 20 : window.innerWidth - 200;
        const y = 20;

        // Enhanced player name label
        const label = document.createElement('div');
        label.className = 'pl-label';
        label.textContent = nick;
        label.style.cssText = `
            position: absolute;
            font: bold 18px 'Arial', sans-serif;
            text-shadow: 2px 2px 4px #000;
            pointer-events: none;
            z-index: 10;
            white-space: nowrap;
            color: #${tint.toString(16).padStart(6, '0')};
            left: ${x}px;
            top: ${y}px;
            background: rgba(0,0,0,0.5);
            padding: 5px 10px;
            border-radius: 8px;
            backdrop-filter: blur(5px);
        `;
        document.body.appendChild(label);

        // Enhanced health bar container
        const container = document.createElement('div');
        container.className = 'pl-bar-container';
        container.style.cssText = `
            position: absolute;
            display: flex;
            flex-direction: column;
            gap: 3px;
            width: 180px;
            pointer-events: none;
            z-index: 10;
            left: ${x}px;
            top: ${y + 35}px;
        `;

        // Main health bar with gradient
        const currentBar = document.createElement('div');
        currentBar.className = 'pl-bar current';
        currentBar.style.cssText = `
            position: relative;
            height: 18px;
            background: linear-gradient(45deg, #333, #555);
            border: 2px solid #000;
            border-radius: 6px;
            overflow: hidden;
            box-shadow: inset 0 2px 4px rgba(0,0,0,0.5);
        `;

        const currentFill = document.createElement('div');
        currentFill.className = 'fill';
        currentFill.style.cssText = `
            position: absolute;
            left: 0;
            top: 0;
            height: 100%;
            width: 100%;
            background: linear-gradient(90deg, #${tint.toString(16).padStart(6, '0')}, #${(tint + 0x202020).toString(16).padStart(6, '0')});
            transition: width 0.5s ease;
            box-shadow: inset 0 1px 2px rgba(255,255,255,0.3);
        `;

        const hpText = document.createElement('div');
        hpText.className = 'hp-text';
        hpText.style.cssText = `
            position: absolute;
            inset: 0;
            display: flex;
            align-items: center;
            justify-content: center;
            color: #fff;
            font-size: 12px;
            font-weight: bold;
            text-shadow: 1px 1px 2px #000;
        `;
        hpText.textContent = '100/100';

        currentBar.appendChild(currentFill);
        currentBar.appendChild(hpText);
        container.appendChild(currentBar);

        // Round health bars
        for (let i = 0; i < 3; i++) {
            const roundBar = document.createElement('div');
            roundBar.className = 'pl-bar';
            roundBar.style.cssText = `
                position: relative;
                height: 8px;
                background: linear-gradient(45deg, #333, #444);
                border: 1px solid #000;
                border-radius: 4px;
                overflow: hidden;
            `;

            const roundFill = document.createElement('div');
            roundFill.className = 'fill';
            roundFill.style.cssText = `
                position: absolute;
                left: 0;
                top: 0;
                height: 100%;
                width: 100%;
                background: linear-gradient(90deg, #888, #aaa);
            `;

            roundBar.appendChild(roundFill);
            container.appendChild(roundBar);
        }

        document.body.appendChild(container);

        // Store UI references
        this.ui.labels[key] = label;
        this.ui.bars[key] = {
            current: {bar: currentBar, fill: currentFill, text: hpText},
            rounds: Array.from(container.querySelectorAll('.pl-bar:not(.current)'))
        };
    }

    updateHealthBars() {
        Object.keys(this.players).forEach(key => {
            const ui = this.ui.bars[key];
            if (!ui) return;

            const healthPercent = Math.max(0, this.currentHealth[key]) / 100;
            ui.current.fill.style.width = `${healthPercent * 100}%`;
            ui.current.text.textContent = `${Math.max(0, this.currentHealth[key])}/100`;

            // Update health bar color based on health
            const hue = healthPercent * 120; // Red to green
            ui.current.fill.style.background = `linear-gradient(90deg, hsl(${hue}, 100%, 50%), hsl(${hue}, 80%, 60%))`;
        });
    }

    createGameUI() {
        if (typeof document === 'undefined') return;

        // Round counter
        const roundCounter = document.createElement('div');
        roundCounter.style.cssText = `
            position: absolute;
            top: 20px;
            left: 50%;
            transform: translateX(-50%);
            font: bold 20px Arial;
            color: #fff;
            text-shadow: 2px 2px 4px #000;
            z-index: 10;
            background: rgba(0,0,0,0.7);
            padding: 10px 20px;
            border-radius: 10px;
            backdrop-filter: blur(10px);
        `;
        roundCounter.textContent = `Runda ${this.currentRound} - 0:0`;
        document.body.appendChild(roundCounter);
        this.ui.round = roundCounter;

        // Controls info
        const controls = document.createElement('div');
        controls.style.cssText = `
            position: absolute;
            bottom: 20px;
            left: 20px;
            font: 14px Arial;
            color: #fff;
            text-shadow: 1px 1px 2px #000;
            z-index: 10;
            background: rgba(0,0,0,0.6);
            padding: 10px;
            border-radius: 8px;
            line-height: 1.4;
        `;
        controls.innerHTML = `
            <strong>Controale:</strong><br>
            Jucător A: WASD (mișcare), SPACE (lovitură)<br>
            Jucător B: Săgeți (mișcare), ENTER (lovitură)
        `;
        document.body.appendChild(controls);

        // Add CSS animations
        const style = document.createElement('style');
        style.textContent = `
            @keyframes hitEffect {
                0% { transform: translateY(0) scale(1); opacity: 1; }
                50% { transform: translateY(-30px) scale(1.2); opacity: 0.8; }
                100% { transform: translateY(-60px) scale(0.8); opacity: 0; }
            }
        `;
        document.head.appendChild(style);
    }

    animatePunch(player, elapsed) {
        // 0 → 1 pe durata loviturii
        const p = Math.min(elapsed / this.PUNCH_DURATION, 1);

        // easing cubic: accelerează puternic, apoi frânează înapoi
        //   p < 0.5  =>  out-quad  (dus)
        //   p >=0.5  =>  in-quad   (revenire)
        const k = p < 0.5 ? (2*p*p) : (1 - 2*(1-p)*(1-p));

        // braț + mănușă
        player.rightArm.rotation.x  = -Math.PI * 0.9 * k;   // -160° în vârf
        player.rightGlove.position.z =
            player.originalPositions.rightGlove.z + 0.35 * k;

        // ușoară rotație de trunchi & cap
        player.body.rotation.y =  0.1 * k * player.dir;
        player.head.position.x =  0.05 * k * player.dir;
    }

}