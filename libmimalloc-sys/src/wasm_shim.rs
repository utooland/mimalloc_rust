use wasm_bindgen::{prelude::wasm_bindgen, JsCast};

#[wasm_bindgen]
extern "C" {
    #[wasm_bindgen(js_namespace = ["globalThis", "Date"], js_name = now)]
    fn date_now() -> Option<f64>;
}

#[no_mangle]
pub unsafe extern "C" fn emscripten_date_now() -> std::ffi::c_double {
    date_now().expect("Date.now() not available")
}

#[no_mangle]
pub unsafe extern "C" fn getentropy(buffer: *mut u8, length: usize) -> i32 {
    if buffer.is_null() {
        return -1;
    }

    let crypto = if let Ok(c) = js_sys::global()
        .dyn_ref::<web_sys::WorkerGlobalScope>()
        .expect("Not supported out of web worker")
        .crypto()
    {
        c
    } else {
        return -1;
    };

    if crypto
        .get_random_values_with_u8_array(std::slice::from_raw_parts_mut(buffer, length))
        .is_ok()
    {
        0
    } else {
        -1
    }
}

#[no_mangle]
pub unsafe extern "C" fn emscripten_get_heap_size() -> u32 {
    wasm_bindgen::memory()
        .dyn_into::<js_sys::WebAssembly::Memory>()
        .expect("Failed to get WebAssembly::Memory instance")
        .buffer()
        .dyn_ref::<js_sys::SharedArrayBuffer>()
        .expect("Not a SharedArrayBuffer")
        .byte_length() as u32
}

#[no_mangle]
pub unsafe extern "C" fn emscripten_resize_heap(new_size_bytes: u32) -> bool {
    let memory_value = wasm_bindgen::memory();
    let memory = memory_value
        .dyn_into::<js_sys::WebAssembly::Memory>()
        .expect("Failed to get WebAssembly::Memory instance.");

    let current_pages = memory
        .buffer()
        .dyn_ref::<js_sys::SharedArrayBuffer>()
        .expect("Not a SharedArrayBuffer")
        .byte_length()
        / 65536;

    let new_pages = new_size_bytes.div_ceil(65536);

    if new_pages <= current_pages {
        return true;
    }

    let pages_to_grow = new_pages - current_pages;

    let result = memory.grow(pages_to_grow);

    result as i32 >= 0
}
