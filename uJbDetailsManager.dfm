object JbDetailsManager: TJbDetailsManager
  OldCreateOrder = False
  OnDestroy = DataModuleDestroy
  Height = 86
  Width = 318
  object fdqPkd: TFDQuery
    CachedUpdates = True
    Connection = ConnectionManager.fdcMain
    UpdateOptions.AssignedValues = [uvCheckRequired, uvCheckReadOnly, uvCheckUpdatable]
    UpdateOptions.CheckRequired = False
    UpdateOptions.CheckReadOnly = False
    UpdateOptions.CheckUpdatable = False
    Left = 24
    Top = 24
  end
  object fdqBranch: TFDQuery
    CachedUpdates = True
    Connection = ConnectionManager.fdcMain
    Left = 80
    Top = 24
  end
  object fdqDepend: TFDQuery
    CachedUpdates = True
    Connection = ConnectionManager.fdcMain
    UpdateOptions.AssignedValues = [uvCheckRequired, uvCheckReadOnly, uvCheckUpdatable]
    Left = 144
    Top = 24
  end
  object fdqRepresentation: TFDQuery
    CachedUpdates = True
    Connection = ConnectionManager.fdcMain
    Left = 224
    Top = 24
  end
end
