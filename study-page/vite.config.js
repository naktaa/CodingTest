import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';
export default defineConfig({
    plugins: [react()],
    server: { watch: { usePolling: true, interval: 750, ignored: ['**/node_modules/**', '**/dist/**', '**/.git/**'] } },
    build: {
        rollupOptions: {
            output: {
                manualChunks(id) {
                    if (id.includes('node_modules/react') || id.includes('node_modules/scheduler')) return 'react';
                    if (id.includes('node_modules/prismjs')) return 'code-highlight';
                    if (id.includes('/src/data/solutions.json')) return 'my-solutions';
                    if (id.includes('/src/content/topics/') || id.includes('/templates/')) return 'algorithm-notes';
                }
            }
        }
    }
});
