import Log from '../../Debug/Log';
import Tag from '../../Debug/Tag';

/**
 * Throttle 节流器: 限制任务执行频率，确保在指定时间间隔内最多执行一次
 * 使用场景：
 * - DOM 事件节流（resize, scroll, input 等）
 * - 频繁的 API 调用限流
 * - 高频状态更新的性能优化
 */
export default class Throttle {
    private static readonly TAG = Tag.throttle;
    private static readonly MIN_TIMEOUT = 10; // 最小节流时间 10ms
    
    private taskCount = 0;          // 待执行任务计数
    private isLocked = false;       // 任务锁状态
    private timerId: number | null = null;  // 定时器 ID
    
    private readonly timeout: number;       // 节流时间间隔
    private readonly taskToRun: Function;   // 要执行的任务
    
    /**
     * 构造函数
     * @param timeout 节流时间间隔（毫秒），最小值 10ms
     * @param task 要执行的任务函数
     */
    constructor(timeout: number, task: Function) {
        Log.d('========== 创建节流器 ==========', Throttle.TAG);
        
        // 参数验证
        if (typeof task !== 'function') {
            Log.e('任务参数必须是函数', Throttle.TAG);
            throw new TypeError('Throttle: task must be a function');
        }
        
        if (typeof timeout !== 'number' || timeout < Throttle.MIN_TIMEOUT) {
            Log.w(`⚠️ timeout参数无效 (${timeout}ms)，使用最小值 ${Throttle.MIN_TIMEOUT}ms`, Throttle.TAG);
            this.timeout = Throttle.MIN_TIMEOUT;
        } else {
            this.timeout = timeout;
        }
        
        this.taskToRun = task;
        
        Log.d(`✅ 节流器创建成功: 间隔=${this.timeout}ms, 任务=${task.name || 'anonymous'}`, Throttle.TAG);
    }

    /**
     * 提交任务到节流队列
     * 如果当前没有任务在执行，立即执行
     * 如果有任务在执行，累加计数，等待解锁后执行
     */
    postTask(): void {
        this.taskCount++;
        
        if (!this.isLocked) {
            Log.d(`📥 提交任务: 计数=${this.taskCount}, 状态=🔓解锁 => 立即执行`, Throttle.TAG);
            this.executeTask();
        } else {
            Log.d(`📥 提交任务: 计数=${this.taskCount}, 状态=🔒锁定 => 等待执行`, Throttle.TAG);
        }
    }

    /**
     * 取消所有待执行的任务
     * 清空任务计数，但不会中断正在执行的任务
     */
    cancel(): void {
        const cancelledTasks = this.taskCount;
        Log.d(`🚫 取消任务: 待执行任务数=${cancelledTasks}`, Throttle.TAG);
        
        this.taskCount = 0;
        
        // 如果有待执行的定时器，清除它
        if (this.timerId !== null) {
            Log.d('清除定时器', Throttle.TAG);
            clearTimeout(this.timerId);
            this.timerId = null;
        }
        
        if (cancelledTasks > 0) {
            Log.d(`✅ 已取消 ${cancelledTasks} 个待执行任务`, Throttle.TAG);
        }
    }

    /**
     * 销毁节流器
     * 清理所有资源，取消待执行任务
     */
    destroy(): void {
        Log.info('🗑️ 销毁节流器', Throttle.TAG);
        this.cancel();
        this.isLocked = false;
        Log.d('节流器已销毁，资源已清理', Throttle.TAG);
    }

    /**
     * 执行任务
     * 私有方法，负责实际的任务执行和节流控制
     * 注意：一次执行会处理所有累积的任务请求，因此执行后会清空所有待执行任务
     */
    private executeTask(): void {
        const startTime = Date.now();
        const pendingTaskCount = this.taskCount;
        Log.d(`⚡ 开始执行任务 (时间戳: ${startTime}, 合并处理${pendingTaskCount}个待执行任务)`, Throttle.TAG);
        
        // 加锁并清空任务计数，因为一次执行就处理了所有累积的变更
        this.lock();
        
        try {
            // 执行任务（一次执行即可处理所有累积的状态变更）
            Log.d(`调用任务函数 (合并${pendingTaskCount}次请求)...`, Throttle.TAG);
            this.taskToRun();
            
            const executionTime = Date.now() - startTime;
            Log.d(`✅ 任务执行完成，耗时: ${executionTime}ms, 已处理${pendingTaskCount}次累积请求`, Throttle.TAG);
            
            // 调度解锁
            this.scheduleUnlock(startTime);
            
        } catch (error) {
            // 错误处理：确保即使任务失败，也能解锁
            const executionTime = Date.now() - startTime;
            Log.e(`❌ 任务执行失败 (耗时: ${executionTime}ms): ${error}`, Throttle.TAG, error as Error);
            
            // 立即解锁，避免死锁
            Log.w('紧急解锁以避免死锁', Throttle.TAG);
            this.unlock();
        }
    }

    /**
     * 加锁并清空任务计数
     */
    private lock(): void {
        const previousCount = this.taskCount;
        this.isLocked = true;
        this.taskCount = 0;
        Log.d(`🔒 加锁: 时间=${Date.now()}, 清空待执行任务=${previousCount}个`, Throttle.TAG);
    }

    /**
     * 调度解锁操作
     * 修复：使用固定的 timeout，从任务开始时间计算
     * @param startTime 任务开始时间
     */
    private scheduleUnlock(startTime: number): void {
        // 计算应该在何时解锁
        const unlockTime = startTime + this.timeout;
        const now = Date.now();
        const delay = Math.max(0, unlockTime - now);
        
        Log.d(`⏰ 调度解锁: ${delay}ms后 (配置间隔: ${this.timeout}ms, 目标时间: ${unlockTime})`, Throttle.TAG);
        
        // 清除之前的定时器（如果有）
        if (this.timerId !== null) {
            Log.d('清除旧定时器', Throttle.TAG);
            clearTimeout(this.timerId);
        }
        
        // 设置新的定时器
        this.timerId = window.setTimeout(() => {
            this.timerId = null;
            Log.d('⏰ 定时器触发，准备解锁', Throttle.TAG);
            this.unlock();
        }, delay);
    }

    /**
     * 解锁
     * 如果在锁定期间又有新任务提交（taskCount > 0），则立即执行一次
     * 注意：同一任务的多次请求会被合并为一次执行
     */
    private unlock(): void {
        this.isLocked = false;
        
        if (this.taskCount > 0) {
            const pendingCount = this.taskCount;
            Log.d(`🔓 解锁: 时间=${Date.now()}, 锁定期间累积了${pendingCount}个新请求 => 立即执行`, Throttle.TAG);
            
            // 立即执行，不需要 setTimeout(0)
            // 因为一次执行就能处理所有累积的请求
            this.executeTask();
        } else {
            Log.d(`🔓 解锁: 时间=${Date.now()}, 锁定期间无新请求`, Throttle.TAG);
        }
    }

    /**
     * 获取当前状态（用于调试）
     */
    getState(): { isLocked: boolean; taskCount: number; timeout: number } {
        const state = {
            isLocked: this.isLocked,
            taskCount: this.taskCount,
            timeout: this.timeout,
        };
        Log.d(`获取状态: 锁定=${state.isLocked ? '🔒' : '🔓'}, 待执行=${state.taskCount}, 间隔=${state.timeout}ms`, Throttle.TAG);
        return state;
    }
}
