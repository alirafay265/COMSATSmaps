const express = require('express');
const { exec } = require('child_process');
const path = require('path');
const cors = require('cors');

const app = express();
const PORT = 3000;

// Middleware
app.use(cors());
app.use(express.json());
app.use(express.static('.')); // Serve static files from current directory

// Path to compiled C++ executable
const CPP_EXECUTABLE = 'navigation_engine.exe';

// Route to get all available locations
app.get('/api/locations', (req, res) => {
    exec(CPP_EXECUTABLE, (error, stdout, stderr) => {
        if (error) {
            console.error('Error getting locations:', error);
            return res.status(500).json({ 
                error: 'Failed to get locations',
                details: 'Make sure navigation_engine is compiled and executable'
            });
        }
        
        if (stderr) {
            console.error('C++ stderr:', stderr);
        }
        
        try {
            const data = JSON.parse(stdout.trim());
            res.json(data);
        } catch (parseError) {
            console.error('JSON parse error:', parseError);
            console.error('Raw output:', stdout);
            res.status(500).json({ error: 'Invalid response format from navigation engine' });
        }
    });
});

// Route to find path between two locations
app.post('/api/navigate', (req, res) => {
    const { source, destination, algorithm = 'dijkstra' } = req.body;
    
    // Validate input
    if (!source || !destination) {
        return res.status(400).json({ error: 'Source and destination are required' });
    }
    
    if (source === destination) {
        return res.status(400).json({ error: 'Source and destination cannot be the same' });
    }
    
    if (!['dijkstra', 'bfs'].includes(algorithm)) {
        return res.status(400).json({ error: 'Invalid algorithm. Use dijkstra or bfs' });
    }
    
    // Execute C++ program with proper escaping
    const command = `${CPP_EXECUTABLE} "${source}" "${destination}" "${algorithm}"`;
    
    console.log(`Executing: ${command}`);
    
    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error('Error executing C++ program:', error);
            return res.status(500).json({ 
                error: 'Failed to calculate route',
                details: error.message
            });
        }
        
        if (stderr) {
            console.error('C++ stderr:', stderr);
        }
        
        try {
            const result = JSON.parse(stdout.trim());
            
            if (result.error) {
                return res.status(404).json(result);
            }
            
            // Add metadata
            result.timestamp = new Date().toISOString();
            result.source = source;
            result.destination = destination;
            
            console.log(`Path found: ${result.path?.length || 0} steps, distance: ${result.distance}`);
            res.json(result);
            
        } catch (parseError) {
            console.error('JSON parse error:', parseError);
            console.error('Raw C++ output:', stdout);
            res.status(500).json({ 
                error: 'Invalid response format from navigation engine',
                details: parseError.message
            });
        }
    });
});

// Health check endpoint
app.get('/api/health', (req, res) => {
    // Test if C++ executable works
    exec(CPP_EXECUTABLE, (error, stdout, stderr) => {
        const isHealthy = !error && stdout.trim().length > 0;
        res.json({ 
            status: isHealthy ? 'OK' : 'ERROR',
            timestamp: new Date().toISOString(),
            cppExecutable: CPP_EXECUTABLE,
            executableWorking: isHealthy,
            error: error ? error.message : null
        });
    });
});

// Serve the main HTML file
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
});

// Error handling middleware
app.use((err, req, res, next) => {
    console.error('Unhandled error:', err);
    res.status(500).json({ error: 'Internal server error' });
});

// 404 handler
app.use((req, res) => {
    res.status(404).json({ error: 'Endpoint not found' });
});

// Start server
app.listen(PORT, () => {
    console.log(`🚀 COMSATS Campus Navigation Server`);
    console.log(`🌐 Server running at http://localhost:${PORT}`);
    console.log(`\n📍 API Endpoints:`);
    console.log(`   GET  /api/locations - Get all campus locations`);
    console.log(`   POST /api/navigate  - Find route between locations`);
    console.log(`   GET  /api/health    - Health check`);
    console.log(`\n🔧 Setup Instructions:`);
    console.log(`   1. Compile C++: g++ -o navigation_engine navigation.cpp`);
    console.log(`   2. Install deps: npm install express cors`);
    console.log(`   3. Make sure index.html is in the same directory`);
    console.log(`\n✅ Ready to navigate COMSATS Lahore Campus!`);
    
    // Test C++ executable on startup
    exec(CPP_EXECUTABLE, (error) => {
        if (error) {
            console.log(`\n⚠️  Warning: C++ executable not found or not working`);
            console.log(`   Run: g++ -o navigation_engine navigation.cpp`);
        } else {
            console.log(`\n✅ C++ navigation engine is working correctly`);
        }
    });
});

// Graceful shutdown
process.on('SIGINT', () => {
    console.log('\n👋 Shutting down Campus Navigation Server...');
    process.exit(0);
});