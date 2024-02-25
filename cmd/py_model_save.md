    # model.eval()
    # with torch.no_grad():
    #     device_type = "cpu"
    #     model.to(device_type)
    #     traced_model = torch.jit.trace(model, torch.randn(32, 10000, 10).to(device_type))
    #     traced_model.save("model_" + device_type + "_.pt")
    #     exit()


    model.eval()
    with torch.no_grad():
        device_type = "cpu"
        model.to(device_type)
        traced_model = torch.jit.trace_module(model, { 
                                               'forward':torch.randn(32, 10000, 10).to(device_type),
                                               'get_model_name':torch.randn(10, 10).to(device_type),
                                               })
        traced_model.save("model_" + device_type + "_name.pt")
        exit()