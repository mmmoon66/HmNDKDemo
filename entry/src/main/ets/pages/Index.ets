import { hilog } from '@kit.PerformanceAnalysisKit'
import testNapi from 'libentry.so'

@Entry
@Component
struct Index {
  @State message: string = 'Hello World'

  build() {
    Row() {
      Column() {
        Text(this.message)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            hilog.info(0x0000, 'testTag', 'Test NAPI 2 + 3 = %{public}d', testNapi.add(2, 3))
            hilog.info(0x0000, 'testTag', 'Test NAPI 2 - 3 = %{public}d', testNapi.subtract(2, 3))
            hilog.info(0x0000, 'testTag', 'Test NAPI 2 * 3 = %{public}d', testNapi.multiply(2, 3))
            hilog.info(0x0000, 'testTag', 'Test NAPI 2 / 3 = %{public}d', testNapi.divide(2, 3))
            hilog.info(0x0000, 'testTag', 'Test NAPI 5! = %{public}d', testNapi.factorial(5))
            const result = testNapi.twoSum([1, 2, 3], 5)
            console.log(`isArray:${Array.isArray(result)}, length:${result.length}, content:${JSON.stringify(result)}`)
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
