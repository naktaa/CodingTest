import { defineConfig } from '@playwright/test';
export default defineConfig({
    testDir: './tests',
    fullyParallel: false,
    workers: 1,
    reporter: [['list'], ['json', { outputFile: 'test-results/results.json' }]],
    use: {
        baseURL: process.env.STUDY_BASE_URL || 'http://127.0.0.1:5174',
        viewport: { width: 1440, height: 1000 },
        colorScheme: 'light',
        launchOptions: { args: ['--no-sandbox'] },
        trace: 'retain-on-failure'
    },
    webServer: process.env.STUDY_BASE_URL ? undefined : {
        command: 'npm run dev -- --port 5174 --strictPort',
        url: 'http://127.0.0.1:5174',
        reuseExistingServer: !process.env.CI
    }
});
